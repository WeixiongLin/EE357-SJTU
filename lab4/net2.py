"""
dongge
"""


from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import Node
from mininet.log import setLogLevel, info
from mininet.cli import CLI
from mininet.link import TCLink

class NetworkTopo( Topo ):
    "A LinuxRouter connecting three IP subnets"

    # pylint: disable=arguments-differ
    def build( self, **_opts ):
        s2 = self.addSwitch( 's2', ip="10.0.0.112" )

        h3 = self.addHost( 'h3', ip="10.0.0.3" )
        h4 = self.addHost( 'h4', ip="10.0.0.4" )

        for h, s in [ (h3, s2), (h4, s2) ]:
            self.addLink( h, s, bw=10, loss=0, delay='5ms' )


def run():
    "Test linux router"
    topo = NetworkTopo()
    net = Mininet( topo=topo,
                   waitConnected=True,
                   link=TCLink )  # controller is used by s1-s3
    net.start()
    info( '*** Routing Table on Router:\n' )
    # info( net[ 'r0' ].cmd( 'route' ) )
    CLI( net )
    net.stop()


if __name__ == '__main__':
    setLogLevel( 'info' )
    run()
