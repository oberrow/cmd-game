#pragma once
#ifdef __cplusplus
#include "pch.h"
#include "Global.hpp"

#define PRAGMA_WARNING_TEMP_DISABLE(x) __pragma(warning(push, x)) \
__pragma(warning(disable : x))
#define IN_OPT
/*
Macro Parameters :
	* numerator - numerator of the fraction
	* total - what a total could be (example 10)
	* denominator - denominator of the fraction
*/
#define FIND_NUMBER_EQUIVELENT_OF_FRACTION(numerator, total, denominator) numerator * total / denominator

namespace util
{
	std::string DLL CoordToString(COORD _coord);
	typedef void(func_t)(void);
	void DLL DoAsyncTask(std::function<void()> task);
	enum colors
	{
		black,
		blue,
		green,
		cyan,
		red,
		magenta,
		brown,
		lightgray,
		darkgray,
		lightblue,
		lightgreen,
		lightcyan,
		lightred,
		lightmagenta,
		yellow,
		white
	};
	/*
	Returns the local time in a string in a certain format
	For format info go to https://www.cplusplus.com/reference/ctime/strftime/
	Default format is %A, %d %B %Y %H:%M:%S:%m
	*/
	std::string DLL TimeToString(std::string format = "%A, %d %B %Y %H:%M:%S");
	// Clears the Console window
	void DLL clear();
	// Checks if an executable is running
	bool DLL IsProcessRunning(const TCHAR* const executableName);
	/*
		An ads is a feature in NTFS to hide files
		For more detail look here : https://www.youtube.com/watch?v=3BWTo87oCwc
		* If using default constructer you need to call open and call close when you are done if you used open but if using non-default conturucter the object will be raii *
		** If changing open modes please note that it will only affect the output stream **
	*/
	class DLL NTFSads
	{
	public:
		NTFSads();
		NTFSads(const char* file, const char* ADSName, std::ios_base::openmode _ModeO = std::ios_base::out,
			int _Prot = std::ios_base::_Default_open_prot);
		NTFSads(const NTFSads&) = delete;
		const char* file = 0;
		const char* ADSName = 0;
	private:
		bool isDefault = false;
		bool closed = false;
		bool deleted = false;
		int _Prot = 0;
		std::ios_base::openmode _ModeO = 0;
		std::ofstream outADS;
		std::ifstream inADS;
	public:
		void Tructuate();
		~NTFSads();
		bool isClosed();
		// Only works with the default constructer
		void open(const char* file, const char* ADSName, std::ios_base::openmode _ModeO = std::ios_base::out,
			int _Prot = std::ios_base::_Default_open_prot);
		/*Deletes an alternate data stream
		* Closes ads file streams *
		*/
			void DeleteADS();
		/*
			Splits an Alternate Data Stream and a file
			Returns false if both new filename and the other file are the same
			* Closes ads file streams *
		*/
		bool SplitFileFromADS(const char* newFn);
		/* MakeADS expects the filename in util::NTFSads::file to already exist!
		   Makes an Alternate Data Stream
			Returns false if ADS isn't open otherwise it returns true if it returns false
			make sure you called open() if you used the default contructer
		*/
		bool MakeADS();
		// ReadADS Reads from an Alternate Data Stream
		std::string ReadADS();
		/*
		WriteADS Writes to an ADS
		WriteADS Expects the ADS to already exist
		Returns false if the file doesn't exist
		*/
		bool WriteADS(std::string toWrite);
		// Closes the ads
		void close();
	};
	template<typename TP>
	// Converts <TP> into time_t
	time_t DLL to_time_t(TP tp);
	/* Checks for file modification in an infinite loop so you might want to run it in a different thread * Does not work with network paths!
	Usage :
	time_t n = [];
	   // [] being a number
	   std::thread thread{ [&] (void) {
	   while(1)
	   {
			// file.txt can be any file and // ... will be the code that will happen if a change was detected
			// n can be the n variable or a const
			// if you are not using n then delete that line
			// if the 2nd parameter is true it will have a delay if false it will not have a delay and n will be useless
			if(CheckFileModification("file.txt", true, n))
			{
				// ...
			}
	   }
	   } };
	*/
	bool DLL CheckFileModification(std::string file, bool delay,time_t milliseconds = 1000, std::string format = "%A, %d %B %Y %H:%M:%S");
	/* Checks for file modification in a loop that makes the function return true
	   when a change has been detected but if you want to check for modification infinitely
	   you need to make a new thread and put it in a loop * This works with network paths *
	   time_t n = [];
	   // [] being a number
	   std::thread thread{ [&] (void) {
	   while(1)
	   {
			// file.txt can be any file and // ... will be the code that will happen if a change was detected
			// n can be the n variable or a const
			// Last parameter can be 1 or 0 or true or false doesn't matter
			// if the 2nd parameter is true it will have a delay if false it will not have a delay and n will be useless
			// Last parameter can be true or false
			if(CheckFileModification("file.txt", true, n))
			{
				// ...
			}
	   }
	   } };
	*/
	bool DLL CheckFileModification(std::string file, bool delay = 0, time_t milliseconds = 1000, bool reserved = 0);
	int DLL GetFileSize(std::string fn);
	// Might only replaces 1 line!
	void DLL FindAndReplaceFile(const char* _fn, std::string toFind, std::string toReplace);
	/* Outputs 1 character at a time at a specific coordinate with a color
	 Usage:
		LPCSTR text = "[] ";
		for (int i = 0; i < 3; i++)
		{
			util::OutputAtCoordA(GetStdHandle(STD_OUTPUT_HANDLE), 1, &text[i], COORD(i, []), BLUE);
		}
		With [] in COORD() is the Y coordinate
	*/
	void DLL OutputAtCoordA(HANDLE _handle, DWORD _length, LPCSTR _str, COORD _pos, WORD _attrib);
	/* Outputs 1 character at a specific coordinate with a color
	 for more characters do this
	 ***********************************************************
		LPCWSTR text = "[] ";
		for (int i = 0; i < 3; i++)
		{
			util::OutputAtCoordW(GetStdHandle(STD_OUTPUT_HANDLE), 1, &text[i], COORD(i, []), BLUE);
		}
		With [] in COORD() is the Y coordinate
	*/
	void DLL OutputAtCoordW(HANDLE _handle, DWORD _length, LPCWSTR _str, COORD _pos, WORD _attrib);
	// Only works with c-style arrays
	template<typename T>
	void DLL ForEach(T* in, size_t size, func_t toRun);
	// Only works with std::vector
	template<typename T>
	void DLL ForEach(std::vector<T> in, func_t toRun);
	// Checks if a number is even
	bool DLL isEven(int);
	struct DLL RunOnDestruction
	{
	private:
		std::function<func_t> Run;
	public:
		RunOnDestruction(std::function<func_t> Run);
		RunOnDestruction(std::function<func_t> Run, std::function<func_t> RunOnConstruction);
		~RunOnDestruction();

	};
	// Returns true if it found a number in the character return false otherwise
	bool DLL isdigit(char);
	template<typename T>
	// Only works with c style array's
	bool DLL in_array(T* _array, T _is, size_t size);
	// Only works with std::vector
	template<typename T>
	bool DLL in_vector(std::vector<T> _array, T _is);
	// Interupts the program so you can do something else
	void DLL Interrupt(void(Run)(void));
	// Returns true if int num can be divided by divisor without a remainder else returns false
	bool DLL canBeDividedBy(int num, int divisor);
	constexpr int invalid_port = 65536;
	using uint4_t = unsigned int;
	// Contains the port needed for class InternetClient & InternetServerTDP
	class DLL Port
	{
	private:
		uint4_t m_Port;
	public:
		constexpr static int max_port = 65535;
		constexpr static int min_port = 0;
		[[nodiscard]] bool is_invalid() const;
		[[nodiscard]] unsigned int get_port() const;
		Port(uint4_t port);
		friend bool DLL operator==(Port p1, Port p2);
	};
	[[nodiscard]] bool DLL operator==(Port p1, Port p2);
	enum class shutdown_how
	{
		recive,
		send,
		both
		
	};
#define LOG_ERROR(fname, ln, ec) 			std::cout << "An error was occured while calling " << #fname ", Line " << #ln ". Error message : " << ec
	/* 
	* Lets you easily use winsock2 (with tdp)
	* Make sure to call CloseSocket in the object when you're done
	*/ 
	class DLL InternetClientTDP
	{
	private:
		const char*	m_Name = "";
		Port		m_TcpPort = 0;
		SOCKET		m_Socket = 0;
		WSADATA		m_Wsa = { 0 };
		int			m_ECResult = 0;
		sockaddr_in m_Server;
		char		m_LastRetrievedMessage[5000];
		bool m_State = true;
	public:
		InternetClientTDP(const char* name, Port tcp_port);
		~InternetClientTDP();

		/*
		* Shut's down the connection and closes the socket
		* Returns nothing
		* Parameters
		* IN_OPT shutdown_how how can be
		* util::shutdown_how::recive
		* util::shutdown_how::send
		* util::shutdown_how::both
		*/
		void CloseSocket(IN_OPT shutdown_how how = shutdown_how::both);
		/*
		* Send's a message through the socket
		* Returns nothing
		* Parameters
		* IN const char* msg Message to be sent
		*/
		void Send(IN const char* msg);
		/*
		* Recives a message from the socket
		* Returns message that was recived from the socket
		* Parameters
		* No parameters!
		*/
		int Recive();
		/*
		*	Get's the message in the message buffer of the object
		*	Returns message that was retrived from the socket using Recive()
		*	Parameters
		*	No parameters!
		*/
		[[nodiscard]] const char* GetRecivedMessageFromBuffer() const;
		/*
		* Send's and recives message
		* Returns message that was recived from the socket 
		* Parameters 
		* IN const char* msg Message to be sent
		*/
		[[nodiscard]] const char* SendRecive(IN const char* msg);
	};
	[[nodiscard]] std::string DLL ErrorCodeToString(int ecode);
#define DEFAULT_BUFLEN 512
	class DLL InternetServerTDP
	{
	private:
		std::string ErrorCodeToString(int ecode);
		SOCKET	m_ListenSocket = INVALID_SOCKET;
		SOCKET	m_ClientSocket = INVALID_SOCKET;
		Port	m_Port;
		WSADATA	m_WsaData;
		int		m_IResult{};
		int		m_ISendResult{};
		char	m_Recvbuf[DEFAULT_BUFLEN];
		int		m_Recvbuflen = DEFAULT_BUFLEN;
	addrinfo*	m_Result = NULL;
	addrinfo	m_Hints = { 0 };
	public:
		InternetServerTDP(Port port);
		~InternetServerTDP();
		void CloseSocket();
		void AcceptConnectionFromClient();
		void SendMessageToClient(const char* message);
		[[nodiscard]] int ReciveMessageFromClient();
		[[nodiscard]] const char* GetMessageFromBuffer();
	};
}
#endif