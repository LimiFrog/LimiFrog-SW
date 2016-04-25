package com.example.limifrog_v2.communication_queue;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import com.example.limifrog_v2.Constants;

import android.util.Log;

public class CommunicationQueue implements Runnable
{
    private Queue<BleRequest> queue = new LinkedList<BleRequest>();
    private Lock lock = new ReentrantLock();
    private Condition requestAvailable = lock.newCondition();
    private Condition commChannelAvailable = lock.newCondition();
    
    private static final int BLUETOOTH_IDLE = 1001;
    private static final int BLUETOOTH_COMM_IN_PROGRESS = 1002;
    
    private int mState = BLUETOOTH_IDLE;    
    
	public CommunicationQueue()
	{
		new Thread(this, "GenericCommunicationQueue").start();
	}
	
	public void run()
	{
		Log.i(Constants.TAG, "CommunicationQueue thread is running");
		try
		{
			while(true)
			{
				BleRequest request = extractNextRequest();
				Log.i(Constants.TAG, "New request extracted from CommunicationQueue");
				
				if (mState != BLUETOOTH_IDLE)
				{
					lock.lock();
					try
					{
						Log.i(Constants.TAG, "Wait CommChannel availability");				
						commChannelAvailable.await();
						Log.i(Constants.TAG, "CommChannel ready");	
					} finally
					{
						lock.unlock();
					}										
				}
					
				Log.i(Constants.TAG, "Sleep");
	            Thread.sleep(500);
				Log.i(Constants.TAG, "Wake up");
				
				mState = BLUETOOTH_COMM_IN_PROGRESS;
				Log.i(Constants.TAG, "BLUETOOTH_COMM_IN_PROGRESS");
				
				request.processRequest();
			}
			
		} catch (InterruptedException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
		
	public void queueRequest(BleRequest request) throws InterruptedException
	{
		lock.lock();
		try
		{
			Log.i(Constants.TAG, "New request added to CommunicationQueue");
			queue.add(request);
			requestAvailable.signal();
		} finally
		{
			lock.unlock();
		}
	}

	public void answerReceived()
	{
		Log.i(Constants.TAG, "CommChannel answerReceived");		
				
		lock.lock();
		try
		{
			mState = BLUETOOTH_IDLE; 
			Log.i(Constants.TAG, "BLUETOOTH_IDLE");		
			commChannelAvailable.signal();
		} finally
		{
			lock.unlock();
		}		
		
	}
	
	private BleRequest extractNextRequest() throws InterruptedException
	{
		lock.lock();
		try
		{
			if(queue.isEmpty())
			{
				Log.i(Constants.TAG, "Queue is empty. Waiting next request...");		
				requestAvailable.await();
			}

			BleRequest request = queue.remove();
			return request;
		} finally
		{
			lock.unlock();
		}
	}
}
