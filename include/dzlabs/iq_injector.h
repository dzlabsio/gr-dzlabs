#ifndef DZLABS_IQ_INJECTOR_H
#define DZLABS_IQ_INJECTOR_H

#include <dzlabs/api.h>
#include <gnuradio/sync_block.h>



namespace gr
{
    namespace dzlabs
    {
        class DZLABS_API iq_injector : virtual public gr::sync_block
        {
        public:
            typedef boost::shared_ptr<iq_injector> sptr;

            static sptr make(
                int burst_len,
                float burst_interval,
                float stream_sample_rate);
        };

    } // namespace dzlabs
} // namespace gr



#endif // DZLABS_IQ_INJECTOR_H
