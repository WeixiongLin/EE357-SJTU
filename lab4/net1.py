"""
locker
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
        s1 = self.addSwitch( 's1', ip="10.0.0.111" )

        h1 = self.addHost( 'h1', ip="10.0.0.1" )
        h2 = self.addHost( 'h2', ip="10.0.0.2" )

        for h, s in [ (h1, s1), (h2, s1) ]:
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
