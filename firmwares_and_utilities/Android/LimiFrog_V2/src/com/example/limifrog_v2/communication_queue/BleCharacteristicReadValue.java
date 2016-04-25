package com.example.limifrog_v2.communication_queue;

import com.example.limifrog_v2.BleAdapterService;
import com.example.limifrog_v2.Constants;

import android.bluetooth.BluetoothGattCharacteristic;
import android.util.Log;

public class BleCharacteristicReadValue extends BleRequest
{
	private BleAdapterService mBluetoothLeService;
	private String mServiceUuid;
	private String mCharacteristicUuid;
	
	public BleCharacteristicReadValue(BleAdapterService service, String serviceUuid, String characteristicUuid)
	{
		mBluetoothLeService = service;
		mServiceUuid = serviceUuid;
		mCharacteristicUuid = characteristicUuid;	
	}
	
	public void processRequest()
	{
		Log.i(Constants.TAG, "processRequest: Get value for characteristic " + mCharacteristicUuid);	
		
		if(!mBluetoothLeService.readCharacteristic(mServiceUuid, mCharacteristicUuid))
		{
			Log.e(Constants.TAG, "failed to readCharacteristic!");
		}
	}
}
