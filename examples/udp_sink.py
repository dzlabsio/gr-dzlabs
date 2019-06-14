#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: UDP Sink
# Author: DZ Labs, LLC
# Generated: Mon May 20 22:14:12 2019
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import dzlabs
import pmt
import sys
from gnuradio import qtgui


class udp_sink(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "UDP Sink")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("UDP Sink")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "udp_sink")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())


        ##################################################
        # Blocks
        ##################################################
        self.dzlabs_udp_sink_0 = dzlabs.udp_sink('127.0.0.1', '1234', '')
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("TEST"), 1000)



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.dzlabs_udp_sink_0, 'in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "udp_sink")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()


def main(top_block_cls=udp_sink, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
