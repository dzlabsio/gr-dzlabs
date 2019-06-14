#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <gnuradio/io_signature.h>
#include "iq_injector_impl.h"

#include <cstdio> 



namespace gr
{
    namespace dzlabs
    {
        iq_injector::sptr iq_injector::make(
            int burst_len,
            float burst_interval,
            float stream_sample_rate)
        {
            return gnuradio::get_initial_sptr(
                new iq_injector_impl(
                    burst_len,
                    burst_interval,
                    stream_sample_rate));
        }


        iq_injector_impl::iq_injector_impl(
            int burst_len,
            float burst_interval,
            float stream_sample_rate) :
            gr::sync_block(
                "iq_injector",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(1, 1, sizeof(gr_complex)))
        {
            // block parameter(s)
            m_burst_len = (unsigned int) burst_len;
            printf("[*] iq_injector: burst_len = %u\n", burst_len);

            m_burst_interval = burst_interval;
            printf("[*] iq_injector: burst_interval = %f\n", burst_interval);

            m_stream_sample_rate = stream_sample_rate;
            printf("[*] iq_injector: stream_sample_rate = %f\n", stream_sample_rate);

            // input port(s)
            m_port_in = pmt::mp("in");
            message_port_register_in(m_port_in);
            set_msg_handler(m_port_in, boost::bind(&iq_injector_impl::handle_pdu, this, _1));
            
            m_burst = new cfloat[m_burst_len];
            
            m_time_start = 0;
            m_current_time = 0;
            m_next_burst_start = burst_interval * stream_sample_rate;
            
            m_in_burst = false;
            
            for (unsigned int i = 0; i < m_burst_len; i++)
            {
                m_burst[i] = cfloat(1, 1);
            }
        }


        iq_injector_impl::~iq_injector_impl()
        {
            // destructor
            delete m_burst;
        }


        void iq_injector_impl::handle_pdu(pmt::pmt_t pdu)
        {
            // handle PDU
            if (pmt::is_pair(pdu) == false)
            {
                printf("[!] iq_injector: invalid PMT (not a pair)\n");
                return;
            }
            
            pmt::pmt_t pdu_meta = pmt::car(pdu);
            pmt::pmt_t pdu_data = pmt::cdr(pdu);
            size_t pdu_data_len = pmt::length(pdu_data);
            
            if (pmt::is_c32vector(pdu_data) == false)
            {
                printf("[!] iq_injector: incorrect PMT data type (not c32vector)\n");
                return;
            }
            
            if (pdu_data_len != m_burst_len)
            {
                printf("[!] iq_injector: incorrect PMT length (%lu)\n", pdu_data_len);
                return;
            }
            
            std::memcpy(
                m_burst,
                pmt::c32vector_elements(pdu_data, pdu_data_len),
                pdu_data_len * sizeof(gr_complex));
            
        }
        
        int iq_injector_impl::work(
            int noutput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {
            gr_complex* out = (gr_complex*)output_items[0];
            
            unsigned int burst_start = 0;
            
            if ((m_current_time + noutput_items) > m_next_burst_start)
            {
                m_in_burst = true;
                burst_start = (m_current_time + noutput_items) - m_next_burst_start;
                
                m_next_burst_start = m_next_burst_start + (m_burst_interval * m_stream_sample_rate);
                m_burst_index = 0;
            }
            
            if (m_in_burst)
            {
                // finish a burst
                if (noutput_items > (m_burst_len - m_burst_index))
                {
                    std::memcpy(
                        out,
                        &m_burst[m_burst_index],
                        sizeof(gr_complex)*(m_burst_len - m_burst_index));
                    
                    std::memset(
                        &out[m_burst_len-m_burst_index],
                        0,
                        sizeof(gr_complex) * (noutput_items - (m_burst_len - m_burst_index)));
                    
                    m_in_burst = false;
                    m_burst_index = 0;
                }
                // start a burst
                else if (m_burst_index == 0)
                {
                    if (noutput_items > (m_burst_len + burst_start))
                    {
                        std::memset(
                            out,
                            0,
                            sizeof(gr_complex) * burst_start);
                        
                        std::memcpy(
                            &out[burst_start],
                            m_burst,
                            sizeof(gr_complex)*m_burst_len);
                    
                        std::memset(
                            &out[burst_start + m_burst_len],
                            0,
                            sizeof(gr_complex) * (noutput_items - m_burst_len - burst_start));
                    
                    m_in_burst = false;
                    }
                    else
                    {
                        std::memset(
                            out,
                            0,
                            sizeof(gr_complex) * burst_start);
                        
                        std::memcpy(
                            &out[burst_start],
                            m_burst,
                            sizeof(gr_complex)*(noutput_items-burst_start));
                        
                        m_burst_index += (noutput_items-burst_start);
                    }
                }
                // just copy data
                else
                {
                    std::memcpy(
                        out,
                        &m_burst[m_burst_index],
                        sizeof(gr_complex) * noutput_items);
                    
                    m_burst_index += noutput_items;
                }
                
                
            }
            // if not in a burst window, just output 0's
            else
            {
                for (unsigned int i = 0; i < noutput_items; i++)
                {
                    out[i] = cfloat(0,0);
                }
            }
            m_current_time += noutput_items;
            
            consume_each(noutput_items);
            
            return noutput_items;
        }

    } // namespace dzlabs
} // namespace gr
