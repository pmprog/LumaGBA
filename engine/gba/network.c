
#include "../platform.h"

static void network_timer2();
static void network_serial();


static NetworkConnectionCallback network_callback_connection;
static NetworkDataCallback network_callback_data;
static u8 network_ismaster;
static u8 network_currentid;
static u16 network_datatosend = 0xBA;


void network_init(NetworkConnectionCallback ConnectionCallback, NetworkDataCallback DataCallback)
{
    irq_disable(II_TIMER2);  // Enable Timer Interrupt
    irq_disable(II_SERIAL);  // Enable Serial Comms

    network_callback_connection = ConnectionCallback;
    network_callback_data = DataCallback;


    REG_TM2CNT_H = 0x00C1;
    REG_TM2CNT_L = 65000;
    irq_set(II_TIMER2, network_timer2, ISR_DEF); // Prepare Timer 2 for data transmission

    REG_RCNT = R_MODE_MULTI;
    REG_SIOCNT = SIO_MODE_MULTI;
    REG_SIOCNT |= SIO_IRQ | SIOM_115200;
    irq_set(II_SERIAL, network_serial, ISR_DEF); // Prepare Serial for data transmission
}

void network_server_start()
{
    irq_enable(II_TIMER2);  // Enable Timer Interrupt
    irq_enable(II_SERIAL);  // Enable Serial Comms
}

void network_server_stop()
{
    irq_disable(II_TIMER2);  // Enable Timer Interrupt
    irq_disable(II_SERIAL);  // Enable Serial Comms
}

void network_client_start()
{
    irq_enable(II_TIMER2);  // Enable Timer Interrupt
    irq_enable(II_SERIAL);  // Enable Serial Comms
}

void network_client_stop()
{
    irq_disable(II_TIMER2);  // Enable Timer Interrupt
    irq_disable(II_SERIAL);  // Enable Serial Comms
}

void network_sendword(u16 Data)
{
    network_datatosend = Data;
}

static void network_timer2()
{
    /*
    // Only send data if all GBAs are in the correct Multiplayer mode
    if(REG_SIOCNT & 0x08 == 0)
    {
        return;
    }
    */

    REG_SIOMLT_SEND = network_datatosend;   // Don't know if I need to copy this every time, but it'll do no harm for now
    network_ismaster = ~(REG_SIOCNT & 0x04);
    if(network_ismaster != 0)
    {
        REG_SIOCNT |= SIOM_ENABLE;    // Send data on the timer
    }

    // Do I care about this?
    network_currentid = (REG_SIOCNT >> 4) & 0x03;   // Get GBA's player number
}

static void network_serial()
{
    //REG_SIOCNT &= ~SIOM_ENABLE;    // Clear start bit
    network_callback_data(REG_SIOMULTI0, REG_SIOMULTI1, REG_SIOMULTI2, REG_SIOMULTI3);
}
