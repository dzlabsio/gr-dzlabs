#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <gnuradio/io_signature.h>
#include "udp_sink_impl.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>



namespace gr
{
    namespace dzlabs
    {
        udp_sink::sptr udp_sink::make(
            const char* host,
            const char* port)
        {
            return gnuradio::get_initial_sptr(
                new udp_sink_impl(
                    host,
                    port));
        }


        udp_sink_impl::udp_sink_impl(
            const char* host,
            const char* port) :
            gr::block(
                "udp_sink",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0))
        {
            //=================//
            //  BLOCK OPTIONS  //
            //=================//

            printf("[*] udp_sink_impl: host = %s\n", host);
            printf("[*] udp_sink_impl: port = %s\n", port);

            //==============//
            //  UDP CLIENT  //
            //==============//

            m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (m_sockfd == -1)
            {
                fprintf(stderr, "[!] udp_sink_impl: socket() failed (%s)\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            struct addrinfo hints;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_DGRAM;

            int rv = getaddrinfo(host, port, &hints, &m_dst);
            if (rv != 0)
            {
                fprintf(stderr, "[!] udp_sink_impl: getaddrinfo() failed (%s)\n", gai_strerror(rv));
                exit(EXIT_FAILURE);
            }

            //=================//
            //  GNURADIO PORT  //
            //=================//

            m_port_in = pmt::mp("in");
            message_port_register_in(m_port_in);
            set_msg_handler(m_port_in, boost::bind(&udp_sink_impl::HandlePdu, this, _1));
        }


        udp_sink_impl::~udp_sink_impl()
        {
        }


        bool udp_sink_impl::stop()
        {
            freeaddrinfo(m_dst);
            close(m_sockfd);
        }


        void udp_sink_impl::HandlePdu(
            pmt::pmt_t pdu)
        {
            size_t len = 0;
            void* bytes = nullptr;

            if (pmt::is_pair(pdu))
            {
                pmt::pmt_t pdu_data = pmt::cdr(pdu);

                len = pmt::length(pdu_data);
                if (len == 0)
                {
                    fprintf(stderr, "[!] udp_sink_impl: PDU length is zero\n");
                    return;
                }

                if (pmt::is_u8vector(pdu_data))
                {
                    bytes = (uint8_t*)pmt::u8vector_elements(pdu_data, len);
                }
                else
                {
                    fprintf(stderr, "[!] dl_subframe_demod: PDU data not of type \"u8vector\"\n");
                    return;
                }
            }
            else
            {
                fprintf(stderr, "[!] udp_sink_impl: PDU is not a pair\n");
                return;
            }

            ssize_t bytes_sent = sendto(
                m_sockfd, bytes, len, 0, m_dst->ai_addr, m_dst->ai_addrlen);

            if (bytes_sent != len)
            {
                fprintf(stderr, "[!] udp_sink: sent incorrect amount of bytes (%s)\n", strerror(errno));
                freeaddrinfo(m_dst);
                close(m_sockfd);
                exit(EXIT_FAILURE);
            }
        }

    } // namespace dzlabs
} // namespace gr
