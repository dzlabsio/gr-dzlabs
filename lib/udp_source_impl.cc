#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <gnuradio/io_signature.h>
#include "udp_source_impl.h"

#include <cstdio> 



namespace gr
{
    namespace dzlabs
    {
        udp_source::sptr udp_source::make(
            const char* host,
            const char* port)
        {
            return gnuradio::get_initial_sptr(
                new udp_source_impl(
                    host,
                    port));
        }


        udp_source_impl::udp_source_impl(
            const char* host,
            const char* port) :
            gr::block(
                "udp_source",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0))
        {
            //=================//
            //  BLOCK OPTIONS  //
            //=================//

            printf("[*] udp_sink_impl: host = %s\n", host);
            printf("[*] udp_sink_impl: port = %s\n", port);

            //==============//
            //  UDP SERVER  //
            //==============//

            m_data = new uint8_t[MAX_DATAGRAM_SIZE];

            //=================//
            //  GNURADIO PORT  //
            //=================//

            m_port_out = pmt::mp("out");
            message_port_register_out(m_port_out);
        }


        udp_source_impl::~udp_source_impl()
        {
        }


        bool udp_source_impl::stop()
        {
            delete[] m_data;
        }

    } // namespace dzlabs
} // namespace gr
