#pragma once

class FExecStatus;
DECLARE_DELEGATE_RetVal(FExecStatus, FPromiseDelegate); // Check task status

/**
 * Return by async task, used to check status to see whether the task is finished.
 */
class FPromise 
{
private:
	FPromiseDelegate PromiseDelegate;
public:
	FPromise();
	FPromise(FPromiseDelegate InPromiseDelegate);
	FExecStatus CheckStatus();
};

enum FExecStatusType 
{
	OK,
	Error,
	// Support async task
	Pending,
};

/**
 * Present the return value of a command. If the FExecStatusType is pending, check the promise value.
 */
class UNREALCV_API FExecStatus
{
public:
	// Support aync task
	static FExecStatus Pending(FString Message=""); // Useful for async task
	static FExecStatus AsyncQuery(FPromise Promise);

	// The status of the FExecStatus can be changed during the async task
	FString MessageBody;
	FExecStatusType ExecStatusType;

	static FExecStatus OK(FString Message="");
	static FExecStatus InvalidArgument;
	static FExecStatus Error(FString ErrorMessage);
	~FExecStatus();
	FString GetMessage() const; // Convert this ExecStatus to String
	FExecStatus& operator+=(const FExecStatus& InExecStatus);

	FPromise& GetPromise(); 
private:
	FPromise Promise; 
	FExecStatus(FExecStatusType InExecStatusType, FString Message);
	// For query
	FExecStatus(FExecStatusType InExecStatusType, FPromise Promise);
};

bool operator==(const FExecStatus& ExecStatus, const FExecStatusType& ExecStatusEnum);
bool operator!=(const FExecStatus& ExecStatus, const FExecStatusType& ExecStatusEnum);