///////////////////////////////////////////////////////////////////////////////
///
/// \file ThreadSync.hpp
/// Declaration of Thread synchronization classes.
/// 
/// Authors: Chris Peters
/// Copyright 2010, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{
/// Thread Lock
/// Safe to lock multiple times from the same thread
class ThreadLock
{
public:
  ThreadLock();
  ~ThreadLock();
  void Lock();
  void Unlock();

private:
  ZeroDeclarePrivateData(ThreadLock, 48);
};

//Wrapper around an unnamed event.
class OsEvent
{
public:
  OsEvent();
  ~OsEvent();
  void Initialize(bool manualReset = false, bool startSignaled = false);
  void Close();
  void Signal();
  void Reset();
  void Wait();
  OsHandle GetHandle();
private:
  ZeroDeclarePrivateData(OsEvent, 8);
};

const int MaxSemaphoreCount = 0x0FFFFFFF;

//Semaphore class. Multithreaded counter / gatekeeper.
class Semaphore
{
public:
  Semaphore();
  ~Semaphore();
  void Increment();
  void Decrement();
  void Reset();
  void WaitAndDecrement();
private:
  OsHandle mHandle;

  ZeroDeclarePrivateData(Semaphore, 8);
};

/// Not fully implemented as it's currently only needed for interprocess communication
class InterprocessMutex
{
public:
  InterprocessMutex();
  ~InterprocessMutex();

  void Initialize(Status& status, const char* mutexName, bool failIfAlreadyExists = false);

private:
  ZeroDeclarePrivateData(InterprocessMutex, 8);
};

class CountdownEvent
{
public:
  CountdownEvent();

  void IncrementCount();
  void DecrementCount();
  void Wait();

private:
  OsEvent mWaitEvent;
  ThreadLock mThreadLock;
  int mCount;
};

}//namespace Zero
