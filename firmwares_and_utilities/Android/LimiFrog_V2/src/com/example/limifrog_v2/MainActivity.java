package com.example.limifrog_v2;

import java.util.ArrayList;
import java.util.UUID;

import com.example.limifrog_v2.DeviceInfoActivity;
import com.example.limifrog_v2.MainActivity;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends Activity
{

	private BluetoothAdapter mBluetoothAdapter = null;
	private boolean mScanning = false;
	private Handler mHandler = new Handler();
	private ListAdapter mLeDeviceListAdapter;

	private static final long SCAN_TIMEOUT = 5000;

	static class ViewHolder
	{
		public TextView text;

	}

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
		setContentView(R.layout.activity_main);

		// Initializes Bluetooth adapter.
		final BluetoothManager bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
		mBluetoothAdapter = bluetoothManager.getAdapter();

		mLeDeviceListAdapter = new ListAdapter();

		ListView listView = (ListView) this.findViewById(R.id.deviceList);
		listView.setAdapter(mLeDeviceListAdapter);

		listView.setOnItemClickListener(new OnItemClickListener()
			{

				@Override
				public void onItemClick(AdapterView<?> parent, View view, int position, long id)
				{

					if (mScanning)
					{
						setScanState(false);
						mBluetoothAdapter.stopLeScan(mLeScanCallback);
					}

					BluetoothDevice device = mLeDeviceListAdapter.getDevice(position);
					
					Log.i(Constants.TAG, "Selection of device " + device.getName() );	
					Log.i(Constants.TAG, "Address " + device.getAddress() );
					
					Intent intent = new Intent(MainActivity.this, DeviceInfoActivity.class);
					intent.putExtra(DeviceInfoActivity.EXTRAS_DEVICE_NAME, device.getName());
					intent.putExtra(DeviceInfoActivity.EXTRAS_DEVICE_ADDRESS, device.getAddress());
					startActivity(intent);
				}
			});
	}

	public void onScan(View view)
	{
		// check bluetooth is available on on
		if (mBluetoothAdapter == null || !mBluetoothAdapter.isEnabled())
		{
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivity(enableBtIntent);
			return;
		}
		scanLeDevice(!mScanning);
	}

	private void setScanState(boolean value)
	{
		mScanning = value;
		setProgressBarIndeterminateVisibility(value);
		((Button) this.findViewById(R.id.scanButton)).setText(value ? "Stop" : "Scan");
	}

	private void scanLeDevice(final boolean enable)
	{
		if (enable)
		{
			// scan for SCAN_TIMEOUT
			mHandler.postDelayed(new Runnable()
				{
					@Override
					public void run()
					{
						setScanState(false);
						mBluetoothAdapter.stopLeScan(mLeScanCallback);
					}
				}, SCAN_TIMEOUT);

			setScanState(true);
			Log.i(Constants.TAG, "Clear list");
			mLeDeviceListAdapter.clear();
			mLeDeviceListAdapter.notifyDataSetChanged();

			Log.i(Constants.TAG, "And start scan");
			mBluetoothAdapter.startLeScan(mLeScanCallback);
		}
		else
		{
			Log.i(Constants.TAG, "Stop scan");
			setScanState(false);
			mBluetoothAdapter.stopLeScan(mLeScanCallback);
		}
	}

	// Device scan callback.
	private BluetoothAdapter.LeScanCallback mLeScanCallback = new BluetoothAdapter.LeScanCallback()
		{

			@Override
			public void onLeScan(final BluetoothDevice device, int rssi, byte[] scanRecord)
			{

				runOnUiThread(new Runnable()
					{
						@Override
						public void run()
						{
							Log.i(Constants.TAG, "New device found: " +  device.getName() );
							mLeDeviceListAdapter.addDevice(device);
							mLeDeviceListAdapter.notifyDataSetChanged();
						}
					});
			}
		};

	// adaptor
	private class ListAdapter extends BaseAdapter
	{
		private ArrayList<BluetoothDevice> mLeDevices;

		public ListAdapter()
		{
			super();
			mLeDevices = new ArrayList<BluetoothDevice>();

		}

		public void addDevice(BluetoothDevice device)
		{
			if (!mLeDevices.contains(device))
			{
				mLeDevices.add(device);
			}
		}

		public BluetoothDevice getDevice(int position)
		{
			return mLeDevices.get(position);
		}

		public void clear()
		{
			mLeDevices.clear();
		}

		@Override
		public int getCount()
		{
			return mLeDevices.size();
		}

		@Override
		public Object getItem(int i)
		{
			return mLeDevices.get(i);
		}

		@Override
		public long getItemId(int i)
		{
			return i;
		}

		@Override
		public View getView(int i, View view, ViewGroup viewGroup)
		{
			ViewHolder viewHolder;
			// General ListView optimization code.
			if (view == null)
			{
				view = MainActivity.this.getLayoutInflater().inflate(R.layout.list_row, null);
				viewHolder = new ViewHolder();
				viewHolder.text = (TextView) view.findViewById(R.id.textView);
				view.setTag(viewHolder);
			}
			else
			{
				viewHolder = (ViewHolder) view.getTag();
			}
			BluetoothDevice device = mLeDevices.get(i);
			final String deviceName = device.getName();
			if (deviceName != null && deviceName.length() > 0)
				viewHolder.text.setText(deviceName);
			else
				viewHolder.text.setText("unknown device");

			return view;
		}
	}

}
