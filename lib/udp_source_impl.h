#ifndef DZLABS_UDP_SOURCE_IMPL_H
#define DZLABS_UDP_SOURCE_IMPL_H

#include <dzlabs/udp_source.h>

#include <dzlabs/block_options.h>



namespace gr
{
    namespace dzlabs
    {
        class udp_source_impl : public udp_source
        {
        public:
            udp_source_impl(
                const char* host,
                const char* port);

            ~udp_source_impl();

            bool stop() override;

        private:
            uint8_t* m_data;
            pmt::pmt_t m_port_out;
        };

    } // namespace dzlabs
} // namespace gr



#endif // DZLABS_UDP_SOURCE_IMPL_H
