package com.xz.szbinding;


/**
 * Implementation of {@link IInArchive}.
 *
 * @author Boris Brodski
 * @since 4.65-1
 */
//TODO null check all parameters: If null slips through into native code there will be no NPE :(
public final class InArchiveImpl implements IInArchive {


    private long Aresult;


    private int numberOfItems = -1;

    private boolean closed;

    /**
     * {@inheritDoc}
     */
    public void extract(int[] indices, boolean testMode, IArchiveExtractCallback extractCallback)
            throws SevenZipException {
        ensureOpened();
        nativeExtract(indices, testMode, extractCallback);
    }


    /**
     * {@inheritDoc}
     */


    private native void nativeExtract(int[] indicesArray, boolean testMode, IArchiveExtractCallback extractCallback)
            throws SevenZipException;

    private native Object nativeGetArchiveProperty(int propID) throws SevenZipException;


    /**
     * {@inheritDoc}
     */
    @Override
    public Object getArchiveProperty(PropID propID) throws SevenZipException {
        ensureOpened();
        return nativeGetArchiveProperty(propID.getPropIDIndex());
    }

    private native String nativeGetStringArchiveProperty(int propID) throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public String getStringArchiveProperty(PropID propID) throws SevenZipException {
        ensureOpened();
        return nativeGetStringArchiveProperty(propID.getPropIDIndex());
    }

    private native PropertyInfo nativeGetArchivePropertyInfo(int index) throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public PropertyInfo getArchivePropertyInfo(int index) throws SevenZipException {
        ensureOpened();
        return nativeGetArchivePropertyInfo(index);
    }

    @Override
    public ISimpleInArchive getSimpleInterface() {
        return null;
    }

    private native int nativeGetNumberOfArchiveProperties() throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public int getNumberOfArchiveProperties() throws SevenZipException {
        ensureOpened();
        return nativeGetNumberOfArchiveProperties();
    }

    private native int nativeGetNumberOfProperties() throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public int getNumberOfProperties() throws SevenZipException {
        ensureOpened();
        return nativeGetNumberOfProperties();
    }

    private native PropertyInfo nativeGetPropertyInfo(int index) throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public PropertyInfo getPropertyInfo(int index) throws SevenZipException {
        ensureOpened();
        return nativeGetPropertyInfo(index);
    }

    private native void nativeClose() throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public void close() throws SevenZipException {
        if (closed) {
            return;
        }
        closed = true;
        nativeClose();
    }

    private native int nativeGetNumberOfItems() throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public int getNumberOfItems() throws SevenZipException {
        ensureOpened();
        if (numberOfItems == -1) {
            numberOfItems = nativeGetNumberOfItems();
        }
        return numberOfItems;
    }

    private native Object nativeGetProperty(int index, int propID) throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public Object getProperty(int index, PropID propID) throws SevenZipException {
        ensureOpened();
        if (index < 0 || index >= getNumberOfItems()) {
            throw new SevenZipException(
                    "Index out of range. Index: " + index + ", NumberOfItems: " + getNumberOfItems());
        }
        // Correct some returned values
        Object returnValue = nativeGetProperty(index, propID.getPropIDIndex());
        switch (propID) {
            case SIZE:
            case PACKED_SIZE:
                // ARJ archive returns integer sizes (32 bit).
                // Correcting it here, since every other archive returns Long (64 bit).
                if (returnValue instanceof Integer) {
                    return Long.valueOf(((Integer) returnValue).longValue());
                }

                if (returnValue == null ) {
                    return Long.valueOf(0);
                }
                break;
            case IS_FOLDER:
                // Some stream archive formats doesn't set this property.
                if (returnValue == null) {
                    return Boolean.FALSE;
                }
                break;
            case ENCRYPTED:
                // Some stream archive formats doesn't set this property either.
                if (returnValue == null) {
                    return Boolean.FALSE;
                }
                break;
            case TIME_TYPE:
                if (returnValue != null) {
                    return 0;
                }
                break;
        }
        return returnValue;
    }

    private native String nativeGetStringProperty(int index, int propID) throws SevenZipException;

    /**
     * {@inheritDoc}
     */
    public String getStringProperty(int index, PropID propID) throws SevenZipException {
        ensureOpened();
        if (index < 0 || index >= getNumberOfItems()) {
            throw new SevenZipException(
                    "Index out of range. Index: " + index + ", NumberOfItems: " + getNumberOfItems());
        }
        return nativeGetStringProperty(index, propID.getPropIDIndex());
    }

    /**
     * ${@inheritDoc}
     */
    @Override
    public String getArchiveFormat() {
        return "";
    }

    void ensureOpened() throws SevenZipException {
        if (closed) {
            throw new SevenZipException("InArchive closed");
        }
    }

}
