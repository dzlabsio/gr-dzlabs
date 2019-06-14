#ifndef DZLABS_UDP_SINK_H
#define DZLABS_UDP_SINK_H

#include <dzlabs/api.h>
#include <gnuradio/block.h>



namespace gr
{
    namespace dzlabs
    {
        class DZLABS_API udp_sink : virtual public gr::block
        {
        public:
            typedef boost::shared_ptr<udp_sink> sptr;

            static sptr make(
                const char* host,
                const char* port);

            virtual bool stop() = 0;
        };

    } // namespace dzlabs
} // namespace gr



#endif // DZLABS_UDP_SINK_H
