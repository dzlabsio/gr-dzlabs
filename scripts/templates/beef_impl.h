#ifndef DEAD_BEEF_IMPL_H
#define DEAD_BEEF_IMPL_H

#include <dead/beef.h>



namespace gr
{
    namespace dead
    {
        class beef_impl : public beef
        {
        public:
            beef_impl(
                int arg0,
                char* arg1,
                bool arg2);

            ~beef_impl();

            void handle_pdu(pmt::pmt_t pdu);

        private:
            // block parameters
            int m_arg0;
            char* m_arg1;
            bool m_arg2;

            // ports
            pmt::pmt_t m_port_in;
            pmt::pmt_t m_port_out;
        };

    } // namespace dead
} // namespace gr

#endif // DEAD_BEEF_IMPL_H
