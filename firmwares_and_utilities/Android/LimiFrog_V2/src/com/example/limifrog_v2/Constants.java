package com.example.limifrog_v2;

public class Constants
{
	public static final String TAG = "LimiFrog";
	
	public static final String MY_INTENT_SERVICE_EVENT = "MY_INTENT_SERVICE_EVENT";

	// Events sent to the IntentService
	public static final int EXPLORE_DEVICE = 2001;
	
	public static final String EXTRAS_DEVICE_NAME = "BLE_DEVICE_NAME";
	public static final String EXTRAS_DEVICE_ADDRESS = "BLE_DEVICE_ADDRESS";
	
	public static final String UUID_DIALOG_SEMECONDUCTOR_SERIAL_PORT_SERVICE = "0783b03e-8535-b5a0-7140-a304d2495cb7";
	/* Notify Property through which we receive the data from the LimiFrog */
	public static final String UUID_DIALOG_SEMECONDUCTOR_SPS_SERVER_TX = "0783b03e-8535-b5a0-7140-a304d2495cb8";
	/* Write Property through which we send the data to the LimiFrog */	
	public static final String UUID_DIALOG_SEMECONDUCTOR_SPS_SERVER_RX = "0783b03e-8535-b5a0-7140-a304d2495cba";	
}
