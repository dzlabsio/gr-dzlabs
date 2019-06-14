#ifndef DZLABS_UDP_SINK_IMPL_H
#define DZLABS_UDP_SINK_IMPL_H

#include <dzlabs/udp_sink.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>



namespace gr
{
    namespace dzlabs
    {
        class udp_sink_impl : public udp_sink
        {
        public:
            udp_sink_impl(
                const char* host,
                const char* port);

            ~udp_sink_impl();

            bool stop() override;

            void HandlePdu(
                pmt::pmt_t pdu);

        private:
            int m_sockfd;
            struct addrinfo* m_dst;
            pmt::pmt_t m_port_in;
        };

    } // namespace dzlabs
} // namespace gr



#endif // DZLABS_UDP_SINK_IMPL_H
