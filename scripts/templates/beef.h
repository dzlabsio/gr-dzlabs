#ifndef DEAD_BEEF_H
#define DEAD_BEEF_H

#include <dead/api.h>
#include <gnuradio/block.h>



namespace gr
{
    namespace dead
    {
        class DEAD_API beef : virtual public gr::block
        {
        public:
            typedef boost::shared_ptr<beef> sptr;

            static sptr make(
                int arg0,
                char* arg1,
                bool arg2);
        };

    } // namespace dead
} // namespace gr



#endif // DEAD_BEEF_H
