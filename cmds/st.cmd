# This should be a test or example startup script

require daq6510

iocshLoad("$(daq6510_DIR)daq6510.iocsh", "IP=192.168.10.44,P=CstatV-AC:,IOCNAME=ioc25-daq")
