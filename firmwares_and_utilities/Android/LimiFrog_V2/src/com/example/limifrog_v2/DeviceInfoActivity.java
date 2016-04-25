package com.example.limifrog_v2;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Queue;
import java.util.UUID;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import org.json.JSONArray;

import com.example.limifrog_v2.Constants;
import com.example.limifrog_v2.communication_queue.BleCharacteristicReadValue;
import com.example.limifrog_v2.communication_queue.CommunicationQueue;

import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.opengl.GLSurfaceView;

public class DeviceInfoActivity extends Activity
{
	public static final String EXTRAS_DEVICE_NAME = "BLE_DEVICE_NAME";
	public static final String EXTRAS_DEVICE_ADDRESS = "BLE_DEVICE_ADDRESS";
	public static final String EXTRAS_DEVICE_RSSI = "BLE_DEVICE_RSSI";

	public enum ListType
	{
		GATT_SERVICES, GATT_CHARACTERISTICS, GATT_CHARACTERISTIC_DETAILS
	}

	private ArrayList<CharacteristicProperties> characteristic_properties;

	private String mDeviceName;
	private String mDeviceAddress;
	private BleAdapterService mBluetoothLeService;

	CubeSurfaceView m3DView;

	short mMagnetoX, mMagnetoY, mMagnetoZ;
	short mAcceleroX, mAcceleroY, mAcceleroZ;

	int my_counter = 0;

	private CommunicationQueue communicationQueue;
	
	private final ServiceConnection mServiceConnection = new ServiceConnection()
		{

			@Override
			public void onServiceConnected(ComponentName componentName, IBinder service)
			{
				Log.i(Constants.TAG, "onServiceConnected");
				mBluetoothLeService = ((BleAdapterService.LocalBinder) service).getService();
				mBluetoothLeService.setActivityHandler(mMessageHandler);
				Log.i(Constants.TAG, "mBluetoothLeService:" + mBluetoothLeService);

				// Activity bound to service. Connect to Bluetooth device right
				// away
				if (mBluetoothLeService != null)
				{
					Log.i(Constants.TAG, "Request connection to device " + mDeviceAddress);
					if (mBluetoothLeService.connect(mDeviceAddress))
					{
						Log.i(Constants.TAG, "Connection successful. Request supported GATT services");
						mBluetoothLeService.getSupportedGattServices();
					}
					else
					{
						Log.e(Constants.TAG, "failed to connect");
					}
				}
				else
				{
					Log.e(Constants.TAG, "Invalid mBluetoothLeService!!!");
				}
			}

			@Override
			public void onServiceDisconnected(ComponentName componentName)
			{
				Log.i(Constants.TAG, "onServiceDisconnected");
				mBluetoothLeService = null;
				Log.i(Constants.TAG, "mBluetoothLeService: null");
			}
		};

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		Log.i(Constants.TAG, "onCreate");

		super.onCreate(savedInstanceState);

		final Intent intent = getIntent();
		mDeviceName = intent.getStringExtra(EXTRAS_DEVICE_NAME);
		mDeviceAddress = intent.getStringExtra(EXTRAS_DEVICE_ADDRESS);

		// connect to the Bluetooth smart service
		Intent gattServiceIntent = new Intent(this, BleAdapterService.class);
		if (bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE))
		{
			Log.i(Constants.TAG, "Bound to Bluetooth service");
		}
		else
		{
			Log.e(Constants.TAG, "Failed to bind to Bluetooth service!!!");
		}

		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		requestWindowFeature(Window.FEATURE_NO_TITLE);

		m3DView = new CubeSurfaceView(this);
		setContentView(m3DView);
	}

	@Override
	protected void onResume()
	{
		Log.i(Constants.TAG, "onResume");

		super.onResume();

		communicationQueue = new CommunicationQueue();
		
		// The following call resumes a paused rendering thread.
		// If you de-allocated graphic objects for onPause()
		// this is a good place to re-allocate them.
		m3DView.onResume();
	};

	@Override
	protected void onPause()
	{
		Log.i(Constants.TAG, "onPause");

		communicationQueue = null;
		
		super.onPause();

		// The following call pauses the rendering thread.
		// If your OpenGL application is memory intensive,
		// you should consider de-allocating objects that
		// consume significant memory here.
		m3DView.onPause();
	};

	@Override
	protected void onDestroy()
	{
		Log.i(Constants.TAG, "onDestroy");
		super.onDestroy();

		Log.i(Constants.TAG, "unbindService");
		unbindService(mServiceConnection);

		mBluetoothLeService = null;
		Log.i(Constants.TAG, "mBluetoothLeService: null");
	}

	public void onConnect(View view)
	{
		Log.i(Constants.TAG, "onConnect");
		if (mBluetoothLeService != null)
		{
			Log.i(Constants.TAG, "Request connection to device " + mDeviceAddress);
			if (mBluetoothLeService.connect(mDeviceAddress))
			{
				Log.i(Constants.TAG, "Connection successful");
				mBluetoothLeService.getSupportedGattServices();
			}
			else
			{
				Log.e(Constants.TAG, "onConnect: failed to connect");
			}
		}
		else
		{
			Log.i(Constants.TAG, "onConnect: mBluetoothLeService=null");
		}
	}

	public void onRead(View view)
	{
		Log.i(Constants.TAG, "onRead");
		String tag = (String) view.getTag();
		Log.i(Constants.TAG, "onRead:" + view.getTag());
		if (mBluetoothLeService != null)
		{
			String service_uuid = Utility.normaliseUUID(Utility.extractServiceUuidFromTag(tag));
			String characteristic_uuid = Utility.normaliseUUID(Utility.extractCharacteristicUuidFromTag(tag));
			mBluetoothLeService.readCharacteristic(service_uuid, characteristic_uuid);
		}
		else
		{
		}
	}

	public void onWrite(View view)
	{
		Log.i(Constants.TAG, "onWrite");
		String tag = (String) view.getTag();
		String service_uuid = Utility.extractServiceUuidFromTag(tag);
		String characteristic_uuid = Utility.extractCharacteristicUuidFromTag(tag);
		String text = "TODO";
		CharacteristicProperties char_props = new CharacteristicProperties(service_uuid, characteristic_uuid);
		int char_props_inx = characteristic_properties.indexOf(char_props);
		if (char_props_inx == -1)
		{
			Log.e(Constants.TAG, "Error:Could not find characteristic properties");
			return;
		}
		char_props = characteristic_properties.get(char_props_inx);
		if (!char_props.isSupports_write() && !char_props.isSupports_write_without_response())
		{
			Log.e(Constants.TAG, "Error:Writing to characteristic not allowed");
			return;
		}

		if (!Utility.isValidHex(text))
		{
			Log.e(Constants.TAG, "Input is not a valid hex number");
			return;
		}
		if (mBluetoothLeService != null)
		{
			byte[] value = Utility.getByteArrayFromHexString(text);
			mBluetoothLeService.writeCharacteristic(Utility.normaliseUUID(service_uuid), Utility.normaliseUUID(characteristic_uuid), value);
		}
		else
		{
		}
	}

	public void onNotify(View view)
	{
		Log.i(Constants.TAG, "onNotify");
		String tag = (String) view.getTag();
		String service_uuid = Utility.extractServiceUuidFromTag(tag);
		String characteristic_uuid = Utility.extractCharacteristicUuidFromTag(tag);

		boolean state = false;
		CharacteristicProperties char_props = new CharacteristicProperties(service_uuid, characteristic_uuid);
		int char_props_inx = characteristic_properties.indexOf(char_props);
		if (char_props_inx == -1)
		{
			Log.e(Constants.TAG, "Error:Could not find characteristic properties");
			return;
		}
		char_props = characteristic_properties.get(char_props_inx);
		if (!char_props.isSupports_notify())
		{
			Log.e(Constants.TAG, "Error:Notifications not supported");
			return;
		}

		if (mBluetoothLeService != null)
		{
			if (mBluetoothLeService.setNotificationsState(Utility.normaliseUUID(service_uuid), Utility.normaliseUUID(characteristic_uuid), state))
			{

			}
		}
		else
		{
			Log.e(Constants.TAG, "Failed to set notifications state");
		}
	}

	public short two_complement_conversion(byte low_byte, byte high_byte)
	{
		int result;
		short short_result;

		// "byte" is signed. Here is how to convert it to an unsigned byte
		// int i = (int) my_byte;
		// int i = i & 0xFF;
		// The first cast takes place with sign extension where by the Most
		// Significant Bit represents the sign of the value and
		// is duplicated up until it forms an integer.

		// Example:
		// b11011011 = -37 = 0xDB
		// ^ signed byte -37
		// |_________ Most Significant Bit
		//
		// Sign extension due to the cast:
		// 11111111 11111111 11111111 11011011 = signed int -37

		// Then we apply "& 0xFF":
		// 11111111 11111111 11111111 11011011 = signed int -37
		// 00000000 00000000 00000000 11111111 = Mask of 0x000000FF
		// 00000000 00000000 00000000 11011011 = Result of & operation
		int low = ((int) low_byte) & 0xFF;
		int high = ((int) high_byte) & 0xFF;
		// Log.i(Constants.TAG, "low = 0x" + Integer.toHexString(low) );
		// Log.i(Constants.TAG, "high = 0x" + Integer.toHexString(high) );

		result = low + (high << 8);
		// Log.i(Constants.TAG, "result = 0x" + Integer.toHexString(result) +
		// " = " + result);

		short_result = (short) result;
		// Log.i(Constants.TAG, "short_result = 0x" +
		// Integer.toHexString(short_result) + " = " + short_result);

		// Example of result:
		// low = 0x2
		// high = 0xfe
		// result = 0xfe02 = 65026
		// short_result = 0xfffffe02 = -510

		return short_result;
	}

	private static HashMap<String, String> UUIDInstructions = new HashMap<String, String>();
	static
	{
		UUIDInstructions.put("00001800-0000-1000-8000-00805f9b34fb", "Generic Access");
		UUIDInstructions.put("00001801-0000-1000-8000-00805f9b34fb", "Generic Attribute");
		UUIDInstructions.put("00001802-0000-1000-8000-00805f9b34fb", "Immediate Alert");
		UUIDInstructions.put("00001803-0000-1000-8000-00805f9b34fb", "Link Loss");
		UUIDInstructions.put("00001804-0000-1000-8000-00805f9b34fb", "Tx Power");
		UUIDInstructions.put("00001805-0000-1000-8000-00805f9b34fb", "Current Time Service");
		UUIDInstructions.put("00001806-0000-1000-8000-00805f9b34fb", "Reference Time Update Service");
		UUIDInstructions.put("00001807-0000-1000-8000-00805f9b34fb", "Next DST Change Service");
		UUIDInstructions.put("00001808-0000-1000-8000-00805f9b34fb", "Glucose");
		UUIDInstructions.put("00001809-0000-1000-8000-00805f9b34fb", "Health Thermometer");
		UUIDInstructions.put("0000180a-0000-1000-8000-00805f9b34fb", "Device Information");
		UUIDInstructions.put("0000180b-0000-1000-8000-00805f9b34fb", "Network Availability Service");
		UUIDInstructions.put("0000180c-0000-1000-8000-00805f9b34fb", "Watchdog");
		UUIDInstructions.put("0000180d-0000-1000-8000-00805f9b34fb", "Heart Rate");
		UUIDInstructions.put("0000180e-0000-1000-8000-00805f9b34fb", "Phone Alert Status Service");
		UUIDInstructions.put("0000180f-0000-1000-8000-00805f9b34fb", "Battery Service");
		UUIDInstructions.put("00001810-0000-1000-8000-00805f9b34fb", "Blood Pressure");
		UUIDInstructions.put("00001811-0000-1000-8000-00805f9b34fb", "Alert Notification Service");
		UUIDInstructions.put("00001812-0000-1000-8000-00805f9b34fb", "Human Interface Device");
		UUIDInstructions.put("00001813-0000-1000-8000-00805f9b34fb", "Scan Parameters");
		UUIDInstructions.put("00001814-0000-1000-8000-00805f9b34fb", "RUNNING SPEED AND CADENCE");
		UUIDInstructions.put("00001815-0000-1000-8000-00805f9b34fb", "Automation IO");
		UUIDInstructions.put("00001816-0000-1000-8000-00805f9b34fb", "Cycling Speed and Cadence");
		UUIDInstructions.put("00001817-0000-1000-8000-00805f9b34fb", "Pulse Oximeter");
		UUIDInstructions.put("00001818-0000-1000-8000-00805f9b34fb", "Cycling Power Service");
		UUIDInstructions.put("00001819-0000-1000-8000-00805f9b34fb", "Location and Navigation Service");
		UUIDInstructions.put("0000181a-0000-1000-8000-00805f9b34fb", "Continous Glucose Measurement Service");
		UUIDInstructions.put("00002a00-0000-1000-8000-00805f9b34fb", "Device Name");
		UUIDInstructions.put("00002a01-0000-1000-8000-00805f9b34fb", "Appearance");
		UUIDInstructions.put("00002a02-0000-1000-8000-00805f9b34fb", "Peripheral Privacy Flag");
		UUIDInstructions.put("00002a03-0000-1000-8000-00805f9b34fb", "Reconnection Address");
		UUIDInstructions.put("00002a04-0000-1000-8000-00805f9b34fb", "Peripheral Preferred Connection Parameters");
		UUIDInstructions.put("00002a05-0000-1000-8000-00805f9b34fb", "Service Changed");
		UUIDInstructions.put("00002a06-0000-1000-8000-00805f9b34fb", "Alert Level");
		UUIDInstructions.put("00002a07-0000-1000-8000-00805f9b34fb", "Tx Power Level");
		UUIDInstructions.put("00002a08-0000-1000-8000-00805f9b34fb", "Date Time");
		UUIDInstructions.put("00002a09-0000-1000-8000-00805f9b34fb", "Day of Week");
		UUIDInstructions.put("00002a0a-0000-1000-8000-00805f9b34fb", "Day Date Time");
		UUIDInstructions.put("00002a0b-0000-1000-8000-00805f9b34fb", "Exact Time 100");
		UUIDInstructions.put("00002a0c-0000-1000-8000-00805f9b34fb", "Exact Time 256");
		UUIDInstructions.put("00002a0d-0000-1000-8000-00805f9b34fb", "DST Offset");
		UUIDInstructions.put("00002a0e-0000-1000-8000-00805f9b34fb", "Time Zone");
		UUIDInstructions.put("00002a1f-0000-1000-8000-00805f9b34fb", "Local Time Information");
		UUIDInstructions.put("00002a10-0000-1000-8000-00805f9b34fb", "Secondary Time Zone");
		UUIDInstructions.put("00002a11-0000-1000-8000-00805f9b34fb", "Time with DST");
		UUIDInstructions.put("00002a12-0000-1000-8000-00805f9b34fb", "Time Accuracy");
		UUIDInstructions.put("00002a13-0000-1000-8000-00805f9b34fb", "Time Source");
		UUIDInstructions.put("00002a14-0000-1000-8000-00805f9b34fb", "Reference Time Information");
		UUIDInstructions.put("00002a15-0000-1000-8000-00805f9b34fb", "Time Broadcast");
		UUIDInstructions.put("00002a16-0000-1000-8000-00805f9b34fb", "Time Update Control Point");
		UUIDInstructions.put("00002a17-0000-1000-8000-00805f9b34fb", "Time Update State");
		UUIDInstructions.put("00002a18-0000-1000-8000-00805f9b34fb", "Glucose Measurement");
		UUIDInstructions.put("00002a19-0000-1000-8000-00805f9b34fb", "Battery Level");
		UUIDInstructions.put("00002a1a-0000-1000-8000-00805f9b34fb", "Battery Power State");
		UUIDInstructions.put("00002a1b-0000-1000-8000-00805f9b34fb", "Battery Level State");
		UUIDInstructions.put("00002a1c-0000-1000-8000-00805f9b34fb", "Temperature Measurement");
		UUIDInstructions.put("00002a1d-0000-1000-8000-00805f9b34fb", "Temperature Type");
		UUIDInstructions.put("00002a1e-0000-1000-8000-00805f9b34fb", "Intermediate Temperature");
		UUIDInstructions.put("00002a1f-0000-1000-8000-00805f9b34fb", "Temperature in Celsius");
		UUIDInstructions.put("00002a20-0000-1000-8000-00805f9b34fb", "Temperature in Fahrenheit");
		UUIDInstructions.put("00002a21-0000-1000-8000-00805f9b34fb", "Measurement Interval");
		UUIDInstructions.put("00002a22-0000-1000-8000-00805f9b34fb", "Boot Keyboard Input Report");
		UUIDInstructions.put("00002a23-0000-1000-8000-00805f9b34fb", "System ID");
		UUIDInstructions.put("00002a24-0000-1000-8000-00805f9b34fb", "Model Number String");
		UUIDInstructions.put("00002a25-0000-1000-8000-00805f9b34fb", "Serial Number String");
		UUIDInstructions.put("00002a26-0000-1000-8000-00805f9b34fb", "Firmware Revision String");
		UUIDInstructions.put("00002a27-0000-1000-8000-00805f9b34fb", "Hardware Revision String");
		UUIDInstructions.put("00002a28-0000-1000-8000-00805f9b34fb", "Software Revision String");
		UUIDInstructions.put("00002a29-0000-1000-8000-00805f9b34fb", "Manufacturer Name String");
		UUIDInstructions.put("00002a2a-0000-1000-8000-00805f9b34fb", "IEEE 11073-20601 Regulatory Certification Data List");
		UUIDInstructions.put("00002a2b-0000-1000-8000-00805f9b34fb", "Current Time");
		UUIDInstructions.put("00002a2c-0000-1000-8000-00805f9b34fb", "Elevation");
		UUIDInstructions.put("00002a2d-0000-1000-8000-00805f9b34fb", "Latitude");
		UUIDInstructions.put("00002a2e-0000-1000-8000-00805f9b34fb", "Longitude");
		UUIDInstructions.put("00002a2f-0000-1000-8000-00805f9b34fb", "Position 2D");
		UUIDInstructions.put("00002a30-0000-1000-8000-00805f9b34fb", "Position 3D");
		UUIDInstructions.put("00002a31-0000-1000-8000-00805f9b34fb", "Scan Refresh");
		UUIDInstructions.put("00002a32-0000-1000-8000-00805f9b34fb", "Boot Keyboard Output Report");
		UUIDInstructions.put("00002a33-0000-1000-8000-00805f9b34fb", "Boot Mouse Input Report");
		UUIDInstructions.put("00002a34-0000-1000-8000-00805f9b34fb", "Glucose Measurement Context");
		UUIDInstructions.put("00002a35-0000-1000-8000-00805f9b34fb", "Blood Pressure Measurement");
		UUIDInstructions.put("00002a36-0000-1000-8000-00805f9b34fb", "Intermediate Cuff Pressure");
		UUIDInstructions.put("00002a37-0000-1000-8000-00805f9b34fb", "Heart Rate Measurement");
		UUIDInstructions.put("00002a38-0000-1000-8000-00805f9b34fb", "Body Sensor Location");
		UUIDInstructions.put("00002a39-0000-1000-8000-00805f9b34fb", "Heart Rate Control Point");
		UUIDInstructions.put("00002a3a-0000-1000-8000-00805f9b34fb", "Removable");
		UUIDInstructions.put("00002a3b-0000-1000-8000-00805f9b34fb", "Service Required");
		UUIDInstructions.put("00002a3c-0000-1000-8000-00805f9b34fb", "Scientific Temperature in Celsius");
		UUIDInstructions.put("00002a3d-0000-1000-8000-00805f9b34fb", "String");
		UUIDInstructions.put("00002a3e-0000-1000-8000-00805f9b34fb", "Network Availability");
		UUIDInstructions.put("00002a3g-0000-1000-8000-00805f9b34fb", "Alert Status");
		UUIDInstructions.put("00002a40-0000-1000-8000-00805f9b34fb", "Ringer Control Point");
		UUIDInstructions.put("00002a41-0000-1000-8000-00805f9b34fb", "Ringer Setting");
		UUIDInstructions.put("00002a42-0000-1000-8000-00805f9b34fb", "Alert Category ID Bit Mask");
		UUIDInstructions.put("00002a43-0000-1000-8000-00805f9b34fb", "Alert Category ID");
		UUIDInstructions.put("00002a44-0000-1000-8000-00805f9b34fb", "Alert Notification Control Point");
		UUIDInstructions.put("00002a45-0000-1000-8000-00805f9b34fb", "Unread Alert Status");
		UUIDInstructions.put("00002a46-0000-1000-8000-00805f9b34fb", "New Alert");
		UUIDInstructions.put("00002a47-0000-1000-8000-00805f9b34fb", "Supported New Alert Category");
		UUIDInstructions.put("00002a48-0000-1000-8000-00805f9b34fb", "Supported Unread Alert Category");
		UUIDInstructions.put("00002a49-0000-1000-8000-00805f9b34fb", "Blood Pressure Feature");
		UUIDInstructions.put("00002a4a-0000-1000-8000-00805f9b34fb", "HID Information");
		UUIDInstructions.put("00002a4b-0000-1000-8000-00805f9b34fb", "Report Map");
		UUIDInstructions.put("00002a4c-0000-1000-8000-00805f9b34fb", "HID Control Point");
		UUIDInstructions.put("00002a4d-0000-1000-8000-00805f9b34fb", "Report");
		UUIDInstructions.put("00002a4e-0000-1000-8000-00805f9b34fb", "Protocol Mode");
		UUIDInstructions.put("00002a4g-0000-1000-8000-00805f9b34fb", "Scan Interval Window");
		UUIDInstructions.put("00002a50-0000-1000-8000-00805f9b34fb", "PnP ID");
		UUIDInstructions.put("00002a51-0000-1000-8000-00805f9b34fb", "Glucose Features");
		UUIDInstructions.put("00002a52-0000-1000-8000-00805f9b34fb", "Record Access Control Point");
		UUIDInstructions.put("00002a53-0000-1000-8000-00805f9b34fb", "RSC Measurement");
		UUIDInstructions.put("00002a54-0000-1000-8000-00805f9b34fb", "RSC Feature");
		UUIDInstructions.put("00002a55-0000-1000-8000-00805f9b34fb", "SC Control Point");
		UUIDInstructions.put("00002a56-0000-1000-8000-00805f9b34fb", "Digital Input");
		UUIDInstructions.put("00002a57-0000-1000-8000-00805f9b34fb", "Digital Output");
		UUIDInstructions.put("00002a58-0000-1000-8000-00805f9b34fb", "Analog Input");
		UUIDInstructions.put("00002a59-0000-1000-8000-00805f9b34fb", "Analog Output");
		UUIDInstructions.put("00002a5a-0000-1000-8000-00805f9b34fb", "Aggregate Input");
		UUIDInstructions.put("00002a5b-0000-1000-8000-00805f9b34fb", "CSC Measurement");
		UUIDInstructions.put("00002a5c-0000-1000-8000-00805f9b34fb", "CSC Feature");
		UUIDInstructions.put("00002a5d-0000-1000-8000-00805f9b34fb", "Sensor Location");
		UUIDInstructions.put("00002a5e-0000-1000-8000-00805f9b34fb", "Pulse Oximetry Spot-check Measurement");
		UUIDInstructions.put("00002a5f-0000-1000-8000-00805f9b34fb", "Pulse Oximetry Continuous Measurement");
		UUIDInstructions.put("00002a60-0000-1000-8000-00805f9b34fb", "Pulse Oximetry Pulsatile Event");
		UUIDInstructions.put("00002a61-0000-1000-8000-00805f9b34fb", "Pulse Oximetry Features");
		UUIDInstructions.put("00002a62-0000-1000-8000-00805f9b34fb", "Pulse Oximetry Control Point");
		UUIDInstructions.put("00002a63-0000-1000-8000-00805f9b34fb", "Cycling Power Measurement Characteristic");
		UUIDInstructions.put("00002a64-0000-1000-8000-00805f9b34fb", "Cycling Power Vector Characteristic");
		UUIDInstructions.put("00002a65-0000-1000-8000-00805f9b34fb", "Cycling Power Feature Characteristic");
		UUIDInstructions.put("00002a66-0000-1000-8000-00805f9b34fb", "Cycling Power Control Point Characteristic");
		UUIDInstructions.put("00002a67-0000-1000-8000-00805f9b34fb", "Location and Speed Characteristic");
		UUIDInstructions.put("00002a68-0000-1000-8000-00805f9b34fb", "Navigation Characteristic");
		UUIDInstructions.put("00002a69-0000-1000-8000-00805f9b34fb", "Position Quality Characteristic");
		UUIDInstructions.put("00002a6a-0000-1000-8000-00805f9b34fb", "LN Feature Characteristic");
		UUIDInstructions.put("00002a6b-0000-1000-8000-00805f9b34fb", "LN Control Point Characteristic");
		UUIDInstructions.put("00002a6c-0000-1000-8000-00805f9b34fb", "CGM Measurement Characteristic");
		UUIDInstructions.put("00002a6d-0000-1000-8000-00805f9b34fb", "CGM Features Characteristic");
		UUIDInstructions.put("00002a6e-0000-1000-8000-00805f9b34fb", "CGM Status Characteristic");
		UUIDInstructions.put("00002a6f-0000-1000-8000-00805f9b34fb", "CGM Session Start Time Characteristic");
		UUIDInstructions.put("00002a70-0000-1000-8000-00805f9b34fb", "Application Security Point Characteristic");
		UUIDInstructions.put("00002a71-0000-1000-8000-00805f9b34fb", "CGM Specific Ops Control Point Characteristic");
			
		/* Specific to LimiFrog */
		UUIDInstructions.put(Constants.UUID_DIALOG_SEMECONDUCTOR_SERIAL_PORT_SERVICE, "Dialog Semiconductor Serial Port Service");
		UUIDInstructions.put(Constants.UUID_DIALOG_SEMECONDUCTOR_SPS_SERVER_TX, "Dialog Semiconductor SPS Server Tx");
		UUIDInstructions.put(Constants.UUID_DIALOG_SEMECONDUCTOR_SPS_SERVER_RX, "Dialog Semiconductor SPS Server Rx");		
	}

	public static String uuid_lookup(UUID uuid)
	{
		String instruction = UUIDInstructions.get(uuid.toString());
		return instruction == null ? "UNKNOWN UUID" : instruction;
	}

	private static HashMap<Integer, String> propertys = new HashMap<Integer, String>();
	static
	{
		propertys.put(1, "PROPERTY_BROADCAST");
		propertys.put(2, "PROPERTY_READ");
		propertys.put(4, "PROPERTY_WRITE_NO_RESPONSE");
		propertys.put(8, "PROPERTY_WRITE");
		propertys.put(16, "PROPERTY_NOTIFY");
		propertys.put(32, "PROPERTY_INDICATE");
		propertys.put(64, "PROPERTY_SIGNED_WRITE");
		propertys.put(128, "PROPERTY_EXTENDED_PROPS");
	}

	public static String property_lookup(int propertySum, int property)
	{
		if ((propertySum & property) == property)
		{
			String propertyName = propertys.get(property);
			return propertyName == null ? null : propertyName;
		}
		else
		{
			return null;
		}
	}

	public static String decodeProperty(int property)
	{
		String strProperty = null;
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_BROADCAST)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_READ)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_WRITE_NO_RESPONSE)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_WRITE)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_NOTIFY)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_INDICATE)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_SIGNED_WRITE)) != null)
		{
			return strProperty;
		}
		if ((strProperty = property_lookup(property, BluetoothGattCharacteristic.PROPERTY_EXTENDED_PROPS)) != null)
		{
			return strProperty;
		}
		strProperty = "Unknown property";
		return strProperty;
	}

	private void discoverServices()
	{
		if (mBluetoothLeService != null)
		{
			List<BluetoothGattService> bluetoothGattServiceList;
			bluetoothGattServiceList = mBluetoothLeService.getSupportedGattServices();
			Log.i(Constants.TAG, "bluetoothGattServiceList: " + bluetoothGattServiceList);

			for (int serv = 0; serv < bluetoothGattServiceList.size(); serv++)
			{
				String serviceUuid = bluetoothGattServiceList.get(serv).getUuid().toString();

				Log.i(Constants.TAG, "Request characteristics for service " + bluetoothGattServiceList.get(serv));
				Log.i(Constants.TAG, "UUID : " + serviceUuid);
				Log.i(Constants.TAG, "Service name : " + uuid_lookup(bluetoothGattServiceList.get(serv).getUuid()));

				discoverServiceCharacteristics(serviceUuid);
			}
		}
	}

	private void discoverServiceCharacteristics(String serviceUuid)
	{
		if (mBluetoothLeService != null)
		{
			List<BluetoothGattCharacteristic> characteristicList = mBluetoothLeService.getSupportedCharacteristics(serviceUuid);

			Log.i(Constants.TAG, "characteristicList: " + characteristicList);
			for (int i = 0; i < characteristicList.size(); i++)
			{
				String characteristicUuid = characteristicList.get(i).getUuid().toString();
				int property = characteristicList.get(i).getProperties();

				Log.i(Constants.TAG, "CHARACTERISTIC :" + characteristicList.get(i));
				Log.i(Constants.TAG, "CHARACTERISTIC_UUID :" + characteristicUuid);
				Log.i(Constants.TAG, "CHARACTERISTIC_NAME :" + uuid_lookup(characteristicList.get(i).getUuid()));
				Log.i(Constants.TAG, "CHARACTERISTIC_PROPERTY :" + decodeProperty(property));

				if ((property_lookup(property, BluetoothGattCharacteristic.PROPERTY_NOTIFY)) != null)
				{
					Log.i(Constants.TAG, "This characteristic has notification. Register to receive them");
					if(!mBluetoothLeService.setNotificationsState(serviceUuid, characteristicUuid, true))
					{
						Log.e(Constants.TAG, "Failed to set notification state for characteristic " + characteristicUuid );
					}
				}

				if ((property_lookup(property, BluetoothGattCharacteristic.PROPERTY_READ)) != null)
				{
					Log.i(Constants.TAG, "Read permission. Request characteristic's value");

					// Characteristics can be read/writen only one at a time!
					// Use a Queue to read them
					
					BleCharacteristicReadValue request = new BleCharacteristicReadValue(mBluetoothLeService, serviceUuid, characteristicUuid);
					try
					{
						communicationQueue.queueRequest(request);							
					} 
					catch (InterruptedException e)
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}	
				}
				
				if ((property_lookup(property, BluetoothGattCharacteristic.PROPERTY_WRITE_NO_RESPONSE)) != null)
				{
					if(characteristicUuid.equals(Constants.UUID_DIALOG_SEMECONDUCTOR_SPS_SERVER_RX))
					{
						Log.i(Constants.TAG, "Found LimiFrog Tx channel. Send it a hello and my name");
						
						String message = "Hello from " + Build.MODEL;
						Log.i(Constants.TAG, "Message sent to LimiFrog: " + message);
					}
				}
			}
		}
	}
	
	private void processLimiFrogNotification(final byte[] rawValue)
	{
		String text_magneto = "";
		String text_accelero = "";
		
		Log.i(Constants.TAG, "processLimiFrogNotification");
			
		for(int offset=0; offset < rawValue.length; offset++)
		{
			if( (offset + 15) < rawValue.length)
			{
				if( (rawValue[offset+0] == 0x11) && 
				    (rawValue[offset+1] == 0x22) &&
				    (rawValue[offset+2] == 0x33) &&
				    (rawValue[offset+3] == 0x44) )
				{
					StringBuilder stringBuilder = new StringBuilder();
							
					// Offset + 00 = 0x11
					// Offset + 01 = 0x22
					// Offset + 02 = 0x33
					// Offset + 03 = 0x44
					// Offset + 04 = Magneto X low byte
					// Offset + 05 = Magneto X
					// Offset + 06 = Magneto Y low byte
					// Offset + 07 = Magneto Y
					// Offset + 08 = Magneto Z low byte
					// Offset + 09 = Magneto Z
					mMagnetoX = two_complement_conversion(rawValue[offset+4], rawValue[offset+5]);
					mMagnetoY = two_complement_conversion(rawValue[offset+6], rawValue[offset+7]);
					mMagnetoZ = two_complement_conversion(rawValue[offset+8], rawValue[offset+9]);
						
					stringBuilder.append("Magneto  :");
					stringBuilder.append(" X=" + String.format("%5d", mMagnetoX) );
					stringBuilder.append(" Y=" + String.format("%5d", mMagnetoY) );
					stringBuilder.append(" Z=" + String.format("%5d", mMagnetoZ) );	
					text_magneto = stringBuilder.toString();
					
					// Offset + 10 = Accelero X low byte
					// Offset + 11 = Accelero X
					// Offset + 12 = Accelero Y low byte
					// Offset + 13 = Accelero Y
					// Offset + 14 = Accelero Z low byte
					// Offset + 15 = Accelero Z		
					stringBuilder.setLength(0); 	// Clear the stringBuilder
					mAcceleroX = two_complement_conversion(rawValue[offset+10], rawValue[offset+11]);
					mAcceleroY = two_complement_conversion(rawValue[offset+12], rawValue[offset+13]);
					mAcceleroZ = two_complement_conversion(rawValue[offset+14], rawValue[offset+15]);
		
					stringBuilder.append("Accelero :");
					stringBuilder.append(" X=" + String.format("%5d", mAcceleroX) );
					stringBuilder.append(" Y=" + String.format("%5d", mAcceleroY) );
					stringBuilder.append(" Z=" + String.format("%5d", mAcceleroZ) );	
					text_accelero = stringBuilder.toString();	
											
					//my_counter++;
					//float angleTmp = (my_counter % 360);
					
					float angleX = (float) Math.toDegrees(Math.atan2(mMagnetoY, mMagnetoZ));
					float angleY = (float) Math.toDegrees(Math.atan2(mMagnetoZ, mMagnetoX));
					float angleZ = (float) Math.toDegrees(Math.atan2(mMagnetoY, mMagnetoX));

					// Correction for verticality
//					angleX -= 114;
//					angleZ -= 96;						
//					angleY += 103;
					
					Log.i("myAccelero", text_accelero);	
					Log.i("myMagneto", text_magneto);
					Log.i("myMagneto", " => angleX = " + angleX);
					Log.i("myMagneto", " => angleY = " + angleY);
					Log.i("myMagneto", " => angleZ = " + angleZ);
					
					Log.i("myCSV", mMagnetoX + " ; " + mMagnetoY + " ; " +  mMagnetoZ + " ; " + angleZ);
					
					//m3DView.setAngle(-angleX, 0, 0);
					m3DView.setAngle(0, -angleY, 0);
					//m3DView.setAngle(0, 0, -angleZ);
					//m3DView.setAngle(-angleX, -angleY, -angleZ);

				}
			}		
		}
		
	}

	// Service message handler�//////////////////
	private Handler mMessageHandler = new Handler()
		{
			@Override
			public void handleMessage(Message msg)
			{

				Bundle bundle;
				String service_uuid = "";
				String characteristic_uuid = "";
				String parcel_value = "";
				String parcel_text = "";
				byte[] b = null;

				switch (msg.what)
				{
				case BleAdapterService.GATT_CONNECTED:
					Log.i(Constants.TAG, "GATT_CONNECTED");
					// we're connected
					break;
				case BleAdapterService.GATT_DISCONNECT:
					Log.i(Constants.TAG, "GATT_DISCONNECT");
					break;
				case BleAdapterService.GATT_SERVICES_DISCOVERED:
					Log.i(Constants.TAG, "GATT_SERVICES_DISCOVERED");
					// The list of services has been retrieved. We can now parse
					// them
					discoverServices();
					break;

				case BleAdapterService.GATT_CHARACTERISTIC_READ:
					Log.i(Constants.TAG, "GATT_CHARACTERISTIC_READ");
					
					communicationQueue.answerReceived();		
					
					bundle = msg.getData();
					service_uuid = bundle.getString(BleAdapterService.PARCEL_SERVICE_UUID);
					characteristic_uuid = bundle.getString(BleAdapterService.PARCEL_CHARACTERISTIC_UUID);
					Log.i(Constants.TAG, "Handler processing characteristic " + characteristic_uuid + " of service " + service_uuid);
					b = bundle.getByteArray(BleAdapterService.PARCEL_VALUE);
					Log.i(Constants.TAG, "Value=" + Utility.byteArrayAsHexString(b));
					break;
				case BleAdapterService.GATT_CHARACTERISTIC_WRITTEN:
					Log.i(Constants.TAG, "GATT_CHARACTERISTIC_WRITTEN");
					bundle = msg.getData();
					service_uuid = bundle.getString(BleAdapterService.PARCEL_SERVICE_UUID);
					characteristic_uuid = bundle.getString(BleAdapterService.PARCEL_CHARACTERISTIC_UUID);
					Log.i(Constants.TAG, "characteristic " + characteristic_uuid + " of " + service_uuid + " written OK");
					break;
				case BleAdapterService.NOTIFICATION_RECEIVED:
					Log.i(Constants.TAG, "NOTIFICATION_RECEIVED");
					bundle = msg.getData();
					service_uuid = bundle.getString(BleAdapterService.PARCEL_SERVICE_UUID);
					characteristic_uuid = bundle.getString(BleAdapterService.PARCEL_CHARACTERISTIC_UUID);
					Log.i(Constants.TAG, "Handler processing characteristic " + characteristic_uuid + " of service " + service_uuid);
					b = bundle.getByteArray(BleAdapterService.PARCEL_VALUE);
					Log.i(Constants.TAG, "Value=" + Utility.byteArrayAsHexString(b));
					
					if(characteristic_uuid.equals(Constants.UUID_DIALOG_SEMECONDUCTOR_SPS_SERVER_TX))
					{
						// Received limifrog notification
						processLimiFrogNotification(b);
					}					
					break;
				case BleAdapterService.GATT_REMOTE_RSSI:
					Log.i(Constants.TAG, "GATT_REMOTE_RSSI");
					break;
				case BleAdapterService.MESSAGE:
					bundle = msg.getData();
					String text = bundle.getString(BleAdapterService.PARCEL_TEXT);
					Log.i(Constants.TAG, "MESSAGE: " + text);
				}
			}
		};

}
