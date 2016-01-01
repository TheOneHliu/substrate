package com.example.substrate;

public class TestSub {
	public native void hookDemo();
	static {
		System.loadLibrary("substrate");
	}
}
