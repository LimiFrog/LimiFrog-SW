package com.example.limifrog_v2;

import java.util.List;
import java.util.UUID;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothGattDescriptor;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;

public class BleAdapterService extends Service
{

	private static final String TAG = "BDS Android App";

	private BluetoothAdapter mBluetoothAdapter;
	private BluetoothGatt mBluetoothGatt;
	private BluetoothManager mBluetoothManager;
	private Handler mActivityHandler = null;
	private BluetoothDevice device;
	private BluetoothGattDescriptor descriptor;

	public BluetoothDevice getDevice()
	{
		return device;
	}

	// messages sent back to activity
	public static final int GATT_CONNECTED = 1;
	public static final int GATT_DISCONNECT = 2;
	public static final int GATT_SERVICES_DISCOVERED = 3;
	public static final int GATT_CHARACTERISTIC_READ = 4;
	public static final int GATT_REMOTE_RSSI = 5;
	public static final int MESSAGE = 6;
	public static final int NOTIFICATION_RECEIVED = 7;
	public static final int SIMULATED_NOTIFICATION_RECEIVED = 8;
	public static final int GATT_CHARACTERISTIC_WRITTEN = 9;

	// message parms
	public static final String PARCEL_CHARACTERISTIC_UUID = "CHARACTERISTIC_UUID";
	public static final String PARCEL_SERVICE_UUID = "SERVICE_UUID";
	public static final String PARCEL_VALUE = "VALUE";
	public static final String PARCEL_RSSI = "RSSI";
	public static final String PARCEL_TEXT = "TEXT";

	// UUIDs

	public static String ALERTNOTIFICATIONSERVICE_SERVICE_UUID = "1811";

	public static String SUPPORTEDNEWALERTCATEGORY_CHARACTERISTIC_UUID = "2A47";
	public static String NEWALERT_CHARACTERISTIC_UUID = "2A46";
	public static String SUPPORTEDUNREADALERTCATEGORY_CHARACTERISTIC_UUID = "2A48";
	public static String UNREADALERTSTATUS_CHARACTERISTIC_UUID = "2A45";
	public static String ALERTNOTIFICATIONCONTROLPOINT_CHARACTERISTIC_UUID = "2A44";

	public static String BATTERYSERVICE_SERVICE_UUID = "180F";

	public static String BATTERYLEVEL_CHARACTERISTIC_UUID = "2A19";

	public static String DEVICEINFORMATION_SERVICE_UUID = "180A";

	public static String MANUFACTURERNAMESTRING_CHARACTERISTIC_UUID = "2A29";
	public static String MODELNUMBERSTRING_CHARACTERISTIC_UUID = "2A24";
	public static String SERIALNUMBERSTRING_CHARACTERISTIC_UUID = "2A25";
	public static String HARDWAREREVISIONSTRING_CHARACTERISTIC_UUID = "2A27";
	public static String FIRMWAREREVISIONSTRING_CHARACTERISTIC_UUID = "2A26";
	public static String SOFTWAREREVISIONSTRING_CHARACTERISTIC_UUID = "2A28";
	public static String SYSTEMID_CHARACTERISTIC_UUID = "2A23";
	// public static String
	// IEEE11073-20601REGULATORYCERTIFICATIONDATALIST_CHARACTERISTIC_UUID =
	// "2A2A";
	public static String PNPID_CHARACTERISTIC_UUID = "2A50";

	public static String GENERICACCESS_SERVICE_UUID = "1800";

	public static String DEVICENAME_CHARACTERISTIC_UUID = "2A00";
	public static String APPEARANCE_CHARACTERISTIC_UUID = "2A01";
	public static String PERIPHERALPRIVACYFLAG_CHARACTERISTIC_UUID = "2A02";
	public static String RECONNECTIONADDRESS_CHARACTERISTIC_UUID = "2A03";
	public static String PERIPHERALPREFERREDCONNECTIONPARAMETERS_CHARACTERISTIC_UUID = "2A04";

	public static String CLIENT_CHARACTERISTIC_CONFIG = "00002902-0000-1000-8000-00805f9b34fb";

	// Ble Gatt Callback ///////////////////////
	private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback()
		{

			@Override
			public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState)
			{
				if (newState == BluetoothProfile.STATE_CONNECTED)
				{
					sendConsoleMessage("Connected");
					Message msg = Message.obtain(mActivityHandler, GATT_CONNECTED);
					msg.sendToTarget();
					mBluetoothGatt.discoverServices();
				}
				else if (newState == BluetoothProfile.STATE_DISCONNECTED)
				{
					sendConsoleMessage("Disconnected");
					Message msg = Message.obtain(mActivityHandler, GATT_DISCONNECT);
					msg.sendToTarget();
					mBluetoothGatt.close();
				}
			}

			@Override
			public void onServicesDiscovered(BluetoothGatt gatt, int status)
			{
				Message msg = Message.obtain(mActivityHandler, GATT_SERVICES_DISCOVERED);
				msg.sendToTarget();
			}

			@Override
			public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status)
			{
				if (status == BluetoothGatt.GATT_SUCCESS)
				{
					sendConsoleMessage("characteristic read OK");
					Bundle bundle = new Bundle();
					bundle.putString(PARCEL_CHARACTERISTIC_UUID, characteristic.getUuid().toString());
					bundle.putString(PARCEL_SERVICE_UUID, characteristic.getService().getUuid().toString());
					bundle.putByteArray(PARCEL_VALUE, characteristic.getValue());
					Message msg = Message.obtain(mActivityHandler, GATT_CHARACTERISTIC_READ);
					msg.setData(bundle);
					msg.sendToTarget();
				}
				else
				{
					sendConsoleMessage("characteristic read err:" + status);
				}
			}

			@Override
			public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status)
			{
				if (status == BluetoothGatt.GATT_SUCCESS)
				{
					sendConsoleMessage("Characteristic " + characteristic.getUuid().toString() + " written OK");
					Bundle bundle = new Bundle();
					bundle.putString(PARCEL_CHARACTERISTIC_UUID, characteristic.getUuid().toString());
					bundle.putString(PARCEL_SERVICE_UUID, characteristic.getService().getUuid().toString());
					bundle.putByteArray(PARCEL_VALUE, characteristic.getValue());
					Message msg = Message.obtain(mActivityHandler, GATT_CHARACTERISTIC_WRITTEN);
					msg.setData(bundle);
					msg.sendToTarget();
				}
				else
				{
					sendConsoleMessage("characteristic write err:" + status);
				}
			}

			@Override
			public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic)
			{
				Bundle bundle = new Bundle();
				bundle.putString(PARCEL_CHARACTERISTIC_UUID, characteristic.getUuid().toString());
				bundle.putString(PARCEL_SERVICE_UUID, characteristic.getService().getUuid().toString());
				bundle.putByteArray(PARCEL_VALUE, characteristic.getValue());
				Message msg = Message.obtain(mActivityHandler, NOTIFICATION_RECEIVED);
				msg.setData(bundle);
				msg.sendToTarget();
			}

			@Override
			public void onReadRemoteRssi(BluetoothGatt gatt, int rssi, int status)
			{
				if (status == BluetoothGatt.GATT_SUCCESS)
				{
					Bundle bundle = new Bundle();
					bundle.putInt(PARCEL_RSSI, rssi);
					Message msg = Message.obtain(mActivityHandler, GATT_REMOTE_RSSI);
					msg.setData(bundle);
					msg.sendToTarget();
				}
				else
				{
					sendConsoleMessage("RSSI read err:" + status);
				}
			}
		};

	// service binder ////////////////
	private final IBinder mBinder = new LocalBinder();

	public class LocalBinder extends Binder
	{
		BleAdapterService getService()
		{
			return BleAdapterService.this;
		}
	}

	@Override
	public IBinder onBind(Intent intent)
	{
		return mBinder;
	}

	@Override
	public boolean onUnbind(Intent intent)
	{

		if (mBluetoothGatt != null)
		{
			mBluetoothGatt.close();
			mBluetoothGatt = null;
		}

		return super.onUnbind(intent);
	}

	@Override
	public void onCreate()
	{

		if (mBluetoothManager == null)
		{
			mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
			if (mBluetoothManager == null)
			{
				return;
			}
		}

		mBluetoothAdapter = mBluetoothManager.getAdapter();
		if (mBluetoothAdapter == null)
		{
			return;
		}

	}

	// connect to the device
	public boolean connect(final String address)
	{

		if (mBluetoothAdapter == null || address == null)
		{
			sendConsoleMessage("connect: mBluetoothAdapter=null");
			return false;
		}

		device = mBluetoothAdapter.getRemoteDevice(address);
		if (device == null)
		{
			sendConsoleMessage("connect: device=null");
			return false;
		}

		// set auto connect to true
		mBluetoothGatt = device.connectGatt(this, true, mGattCallback);
		sendConsoleMessage("connect: auto connect set to true");
		return true;
	}

	// disconnect from device
	public void disconnect()
	{
		sendConsoleMessage("disconnect");
		if (mBluetoothAdapter == null || mBluetoothGatt == null)
		{
			sendConsoleMessage("disconnect: mBluetoothAdapter|mBluetoothGatt null");
			return;
		}
		mBluetoothGatt.disconnect();
	}

	// set activity the will receive the messages
	public void setActivityHandler(Handler handler)
	{
		mActivityHandler = handler;
	}

	// return list of supported services
	public List<BluetoothGattService> getSupportedGattServices()
	{
		if (mBluetoothGatt == null)
			return null;
		return mBluetoothGatt.getServices();
	}

	// writes a value to a service
	public boolean writeCharacteristic(String serviceUuid, String characteristicUuid, byte[] value)
	{
		Log.d(TAG, "writeCharacteristic serviceUuid=" + serviceUuid + " characteristicUuid=" + characteristicUuid);
		if (mBluetoothAdapter == null || mBluetoothGatt == null)
		{
			sendConsoleMessage("writeCharacteristic: mBluetoothAdapter|mBluetoothGatt null");
			return false;
		}

		BluetoothGattService gattService = mBluetoothGatt.getService(java.util.UUID.fromString(serviceUuid));
		if (gattService == null)
		{
			sendConsoleMessage("writeCharacteristic: gattService null");
			return false;
		}
		BluetoothGattCharacteristic gattChar = gattService.getCharacteristic(java.util.UUID.fromString(characteristicUuid));
		if (gattChar == null)
		{
			sendConsoleMessage("writeCharacteristic: gattChar null");
			return false;
		}
		gattChar.setValue(value);

		return mBluetoothGatt.writeCharacteristic(gattChar);
	}

	// read value from service
	public boolean readCharacteristic(String serviceUuid, String characteristicUuid)
	{
		if (mBluetoothAdapter == null || mBluetoothGatt == null)
		{
			sendConsoleMessage("readCharacteristic: mBluetoothAdapter|mBluetoothGatt null");
			return false;
		}

		BluetoothGattService gattService = mBluetoothGatt.getService(java.util.UUID.fromString(serviceUuid));
		if (gattService == null)
		{
			sendConsoleMessage("readCharacteristic: gattService null");
			return false;
		}
		BluetoothGattCharacteristic gattChar = gattService.getCharacteristic(java.util.UUID.fromString(characteristicUuid));
		if (gattChar == null)
		{
			sendConsoleMessage("readCharacteristic: gattChar null");
			return false;
		}
		return mBluetoothGatt.readCharacteristic(gattChar);
	}
	
	// get characteristics supported by a service
	public List<BluetoothGattCharacteristic> getSupportedCharacteristics(String serviceUuid)
	{
		if (mBluetoothAdapter == null || mBluetoothGatt == null)
		{
			sendConsoleMessage("getSupportedCharacteristics: mBluetoothAdapter|mBluetoothGatt null");
			return null;
		}

		BluetoothGattService gattService = mBluetoothGatt.getService(java.util.UUID.fromString(serviceUuid));
		if (gattService == null)
		{
			sendConsoleMessage("getSupportedCharacteristics: gattService null");
			return null;
		}
		List<BluetoothGattCharacteristic> gattCharList = gattService.getCharacteristics();
		if (gattCharList == null)
		{
			sendConsoleMessage("getSupportedCharacteristics: gattCharList null");
			return null;
		}
		return gattCharList;
	}	

	public boolean setNotificationsState(String serviceUuid, String characteristicUuid, boolean enabled)
	{
		if (mBluetoothAdapter == null || mBluetoothGatt == null)
		{
			sendConsoleMessage("setNotificationsState: mBluetoothAdapter|mBluetoothGatt null");
			return false;
		}

		BluetoothGattService gattService = mBluetoothGatt.getService(java.util.UUID.fromString(serviceUuid));
		if (gattService == null)
		{
			sendConsoleMessage("setNotificationsState: gattService null");
			return false;
		}
		BluetoothGattCharacteristic gattChar = gattService.getCharacteristic(java.util.UUID.fromString(characteristicUuid));
		if (gattChar == null)
		{
			sendConsoleMessage("setNotificationsState: gattChar null");
			return false;
		}
		mBluetoothGatt.setCharacteristicNotification(gattChar, enabled);
		// Enable remote notifications
		descriptor = gattChar.getDescriptor(UUID.fromString(CLIENT_CHARACTERISTIC_CONFIG));
		Log.d(Utility.TAG, "XXXX Descriptor:" + descriptor.getUuid());
		descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
		boolean ok = mBluetoothGatt.writeDescriptor(descriptor);
		return ok;
	}

	public void readRemoteRssi()
	{
		if (mBluetoothAdapter == null || mBluetoothGatt == null)
		{
			return;
		}
		mBluetoothGatt.readRemoteRssi();
	}

	private void sendConsoleMessage(String text)
	{
		Log.d(Utility.TAG, "XXXX " + text);
		Message msg = Message.obtain(mActivityHandler, MESSAGE);
		Bundle data = new Bundle();
		data.putString(PARCEL_TEXT, text);
		msg.setData(data);
		msg.sendToTarget();
	}

}
