#ifndef DZLABS_UDP_SOURCE_H
#define DZLABS_UDP_SOURCE_H

#include <dzlabs/api.h>
#include <gnuradio/block.h>



namespace gr
{
    namespace dzlabs
    {
        class DZLABS_API udp_source : virtual public gr::block
        {
        public:
            typedef boost::shared_ptr<udp_source> sptr;

            static sptr make(
                const char* host,
                const char* port);

            virtual bool stop() = 0;
        };

    } // namespace dzlabs
} // namespace gr



#endif // DZLABS_UDP_SOURCE_H
