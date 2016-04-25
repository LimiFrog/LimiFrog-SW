package com.example.limifrog_v2;

import android.util.Log;

/**
 * Created by mwoolley on 16/02/2015.
 */
 
public class CharacteristicProperties {

    private String service_uuid;
    private String characteristic_uuid;

    private boolean supports_broadcast=false;
    private boolean supports_indicate=false;
    private boolean supports_notify=false;
    private boolean supports_read=false;
    private boolean supports_reliable_write=false;
    private boolean supports_signed_write=false;
    private boolean supports_writable_auxiliaries=false;
    private boolean supports_write=false;
    private boolean supports_write_without_response=false;

    public CharacteristicProperties(String service_uuid, String characteristic_uuid) {
        this.service_uuid = service_uuid;
        this.characteristic_uuid = characteristic_uuid;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        CharacteristicProperties that = (CharacteristicProperties) o;

        if (!characteristic_uuid.equals(that.characteristic_uuid)) return false;
        if (!service_uuid.equals(that.service_uuid)) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = service_uuid.hashCode();
        result = 31 * result + characteristic_uuid.hashCode();
        return result;
    }

    public String getService_uuid() {
        return service_uuid;
    }

    public void setService_uuid(String service_uuid) {
        this.service_uuid = service_uuid;
    }

    public String getCharacteristic_uuid() {
        return characteristic_uuid;
    }

    public void setCharacteristic_uuid(String characteristic_uuid) {
        this.characteristic_uuid = characteristic_uuid;
    }

    public boolean isSupports_broadcast() {
        return supports_broadcast;
    }

    public void setSupports_broadcast(boolean supports_broadcast) {
        this.supports_broadcast = supports_broadcast;
    }

    public boolean isSupports_indicate() {
        return supports_indicate;
    }

    public void setSupports_indicate(boolean supports_indicate) {
        this.supports_indicate = supports_indicate;
    }

    public boolean isSupports_notify() {
        return supports_notify;
    }

    public void setSupports_notify(boolean supports_notify) {
        this.supports_notify = supports_notify;
    }

    public boolean isSupports_read() {
        return supports_read;
    }

    public void setSupports_read(boolean supports_read) {
        this.supports_read = supports_read;
    }

    public boolean isSupports_reliable_write() {
        return supports_reliable_write;
    }

    public void setSupports_reliable_write(boolean supports_reliable_write) {
        this.supports_reliable_write = supports_reliable_write;
    }

    public boolean isSupports_signed_write() {
        return supports_signed_write;
    }

    public void setSupports_signed_write(boolean supports_signed_write) {
        this.supports_signed_write = supports_signed_write;
    }

    public boolean isSupports_writable_auxiliaries() {
        return supports_writable_auxiliaries;
    }

    public void setSupports_writable_auxiliaries(boolean supports_writable_auxiliaries) {
        this.supports_writable_auxiliaries = supports_writable_auxiliaries;
    }

    public boolean isSupports_write() {
        return supports_write;
    }

    public void setSupports_write(boolean supports_write) {
        this.supports_write = supports_write;
    }

    public boolean isSupports_write_without_response() {
        return supports_write_without_response;
    }

    public void setSupports_write_without_response(boolean supports_write_without_response) {
        this.supports_write_without_response = supports_write_without_response;
    }
}
