package com.example.limifrog_v2;

import android.util.Log;

public class Utility
{

	private static final String BLUETOOTH_SIG_UUID_BASE = "0000XXXX-0000-1000-8000-00805f9b34fb";
	public static final String TAG = "Alert Notification";
	private static final String HEX_CHARS = "01234567890ABCDEF";

	public static String normaliseUUID(String uuid)
	{
		String normalised_128_bit_uuid = uuid;
		if (uuid.length() == 4)
		{
			normalised_128_bit_uuid = BLUETOOTH_SIG_UUID_BASE.replace("XXXX", uuid);
		}
		if (uuid.length() == 32)
		{
			normalised_128_bit_uuid = uuid.substring(0, 8) + "-" + uuid.substring(8, 12) + "-" + uuid.substring(12, 16) + "-" + uuid.substring(16, 20) + "-"
					+ uuid.substring(20, 32);
		}
		return normalised_128_bit_uuid;
	}

	public static String extractCharacteristicUuidFromTag(String tag)
	{
		String uuid = "";
		String[] parts = tag.split("_");
		if (parts.length == 4)
		{
			uuid = parts[3];
		}
		return uuid;
	}

	public static String extractServiceUuidFromTag(String tag)
	{
		String uuid = "";
		String[] parts = tag.split("_");
		if (parts.length == 4)
		{
			uuid = parts[2];
		}
		return uuid;
	}

	public static byte[] getByteArrayFromHexString(String hex_string)
	{
		String hex = hex_string.replace(" ", "");
		hex = hex.toUpperCase();

		byte[] bytes = new byte[hex.length() / 2];
		int i = 0;
		int j = 0;
		while (i < hex.length())
		{
			String h1 = hex.substring(i, i + 1);
			String h2 = hex.substring(i + 1, i + 2);
			try
			{
				int b = (Integer.valueOf(h1, 16).intValue() * 16) + (Integer.valueOf(h2, 16).intValue());
				bytes[j++] = (byte) b;
				i = i + 2;
			} catch (NumberFormatException e)
			{
				System.out.println("NFE handling " + h1 + h2 + " with i=" + i);
				throw e;
			}
		}
		return bytes;
	}

	public static String byteArrayAsHexString(byte[] bytes)
	{
		if (bytes == null)
		{
			return "";
		}
		int l = bytes.length;
		StringBuffer hex = new StringBuffer();
		for (int i = 0; i < l; i++)
		{
			if ((bytes[i] >= 0) & (bytes[i] < 16))
				hex.append("0");
			hex.append(Integer.toString(bytes[i] & 0xff, 16).toUpperCase());
		}
		return hex.toString();
	}

	public static boolean isValidHex(String hex_string)
	{
		System.out.println("isValidHex(" + hex_string + ")");
		String hex = hex_string.replace(" ", "");
		hex = hex.toUpperCase();
		int len = hex.length();
		int remainder = len % 2;
		if (remainder != 0)
		{
			System.out.println("isValidHex: not even number of chars");
			return false;
		}
		for (int i = 0; i < len; i++)
		{
			if (!HEX_CHARS.contains(hex.substring(i, i + 1)))
			{
				return false;
			}
		}
		return true;
	}

	public static void main(String args[])
	{
		System.out.println("UUID 1802 = " + Utility.normaliseUUID("1802"));
		System.out.println("isValidHex: 01 02 03 04 05 06 A0 B1 C1 D1 E1 F1=" + isValidHex("01 02 03 04 05 06 A0 B1 C1 D1 E1 F1"));
		System.out.println("isValidHex: 01 02 0X 04 05 06 A0 B1 C1 D1 E1 F1=" + isValidHex("01 02 0X 04 05 06 A0 B1 C1 D1 E1 F1"));
	}

}