#ifndef DZLABS_IQ_INJECTOR_IMPL_H
#define DZLABS_IQ_INJECTOR_IMPL_H

#include "common.h"

#include <dzlabs/iq_injector.h>



namespace gr
{
    namespace dzlabs
    {
        class iq_injector_impl : public iq_injector
        {
        public:
            iq_injector_impl(
                int burst_len,
                float burst_interval,
                float stream_sample_rate);

            ~iq_injector_impl();

            void handle_pdu(pmt::pmt_t pdu);
            
            int work(
                int noutput_items,
                gr_vector_const_void_star &input_items,
                gr_vector_void_star &output_items);

        private:
            // block parameters
            unsigned int    m_burst_len;
            float           m_burst_interval;
            float           m_stream_sample_rate;
            
            cfloat* m_burst;
            
            unsigned int m_burst_index;
            unsigned int m_burst_start;
            unsigned int m_burst_end;
            
            uint64_t m_time_start;
            uint64_t m_current_time;
            uint64_t m_next_burst_start;

            bool m_in_burst;
            // ports
            pmt::pmt_t m_port_in;
        };

    } // namespace dzlabs
} // namespace gr

#endif // DZLABS_IQ_INJECTOR_IMPL_H
