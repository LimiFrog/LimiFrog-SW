package com.example.limifrog_v2.communication_queue;

import com.example.limifrog_v2.BleAdapterService;
import com.example.limifrog_v2.Constants;
import com.example.limifrog_v2.Utility;

import android.bluetooth.BluetoothGattCharacteristic;
import android.util.Log;

public class BleCharacteristicWriteValue extends BleRequest
{
	private BleAdapterService mBluetoothLeService;
	private String mServiceUuid;
	private String mCharacteristicUuid;
	private byte[] mValue;
	
	public BleCharacteristicWriteValue(BleAdapterService service, String serviceUuid, String characteristicUuid, byte[] value)
	{
		mBluetoothLeService = service;
		mServiceUuid = serviceUuid;
		mCharacteristicUuid = characteristicUuid;	
		mValue = value;
	}
	
	public void processRequest()
	{
		Log.i(Constants.TAG, "processRequest: Write value for characteristic " + mCharacteristicUuid);	
		Log.i(Constants.TAG, "Value = " + Utility.byteArrayAsHexString(mValue));
		
		if(!mBluetoothLeService.writeCharacteristic(mServiceUuid, mCharacteristicUuid, mValue))
		{
			Log.e(Constants.TAG, "failed to writeCharacteristic!");
		}
	}
}
