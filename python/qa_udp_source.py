from gnuradio import gr, gr_unittest
from gnuradio import blocks
import dzlabs_swig as dzlabs



class qa_udp_source (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg
        self.tb.run ()
        # check data



if __name__ == '__main__':
    gr_unittest.run(qa_udp_source, "qa_udp_source.xml")
