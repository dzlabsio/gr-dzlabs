#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <gnuradio/io_signature.h>
#include "beef_impl.h"

#include <cstdio> 



namespace gr
{
    namespace dead
    {
        beef::sptr beef::make(
            int arg0,
            char* arg1,
            bool arg2)
        {
            return gnuradio::get_initial_sptr(
                new beef_impl(
                    arg0,
                    arg1,
                    arg2));
        }


        beef_impl::beef_impl(
            int arg0,
            char* arg1,
            bool arg2) :
            gr::block(
                "beef",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0))
        {
            // block parameter(s)
            m_arg0 = arg0;
            printf("[*] beef: arg0 = %d\n", arg0);

            m_arg1 = arg1;
            printf("[*] beef: arg1 = %s\n", arg1);

            m_arg2 = arg2;
            if (arg2 == true)
            {
                printf("[*] beef: arg2 = YES\n");
            }
            else
            {
                printf("[*] beef: arg2 = NO\n");
            }

            // input port(s)
            m_port_in = pmt::mp("in");
            message_port_register_in(m_port_in);
            set_msg_handler(m_port_in, boost::bind(&beef_impl::handle_pdu, this, _1));

            // output port(s)
            m_port_out = pmt::mp("out");
            message_port_register_out(m_port_out);
        }


        beef_impl::~beef_impl()
        {
            // destructor
        }


        void beef_impl::handle_pdu(pmt::pmt_t pdu)
        {
            // handle PDU
        }

    } // namespace dead
} // namespace gr
