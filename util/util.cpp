#include "pch.h"
#include "util.hpp"

#pragma comment(lib,"ws2_32.lib")

namespace util
{
	std::string DLL CoordToString(COORD _coord)
	{
		return std::to_string(_coord.X) + ", " + std::to_string(_coord.Y);
	}
	void DoAsyncTask(std::function<void()> task)
	{
		std::thread async{ task };
		async.detach();
	}
	std::string DLL TimeToString(std::string format)
	{
		std::string formatted = "[ERROR UTIL.DLL] Cannot get time in a string format!";
		std::stringstream ss;
		auto t = std::time(nullptr);
#pragma warning(push, 4996)
#pragma warning(disable : 4996)
		auto tm2 = *localtime(&t);
#pragma warning(pop)
		ss << std::put_time(&tm2, format.c_str());
		if (!ss.str().empty())
		{
			formatted = ss.str();
		}
		return formatted;
	}
	void clear()
	{
		HANDLE h;
		CHAR_INFO v3;
		COORD v4;
		SMALL_RECT v5;
		CONSOLE_SCREEN_BUFFER_INFO v6;
		if ((h = (HANDLE)GetStdHandle(0xFFFFFFF5), (unsigned int)GetConsoleScreenBufferInfo(h, &v6)))
		{
			v5.Right = v6.dwSize.X;
			v5.Bottom = v6.dwSize.Y;
			v3.Char.UnicodeChar = 32;
			v4.Y = -v6.dwSize.Y;
			v3.Attributes = v6.wAttributes;
			v4.X = 0;
			*(DWORD*)&v5.Left = 0;
			ScrollConsoleScreenBufferW(h, &v5, 0, v4, &v3);
			v6.dwCursorPosition = { 0 };
			HANDLE v1 = GetStdHandle(0xFFFFFFF5);
			SetConsoleCursorPosition(v1, v6.dwCursorPosition);
		}
	}
	bool IsProcessRunning(const TCHAR* const executableName) {
		// Credits : https://stackoverflow.com/a/57164620/16564788
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (!Process32First(snapshot, &entry)) {
			CloseHandle(snapshot);
			return false;
		}

		do {
			if (!_tcsicmp(entry.szExeFile, executableName)) {
				CloseHandle(snapshot);
				return true;
			}
		} while (Process32Next(snapshot, &entry));

		CloseHandle(snapshot);
		return false;
	}
	template <typename TP>
	std::time_t to_time_t(TP tp)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
			+ system_clock::now());
		return system_clock::to_time_t(sctp);
	}
	bool DLL isdigit(char _ch)
	{
		bool not_found = false;
		char num[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		for (int i = 0; i < 10; i++)
		{
			if (_ch == num[i])
			{
				return(true);
			}
			else
			{
				not_found = true;
			}
		}
		if (not_found)
		{
			return(false);
		}
	}
	template<typename T>
	void DLL ForEach(T* in, size_t size, func_t _Run)
	{
		for (int i = 0; i < size; i++)
		{
			_Run();
		}
	}
	template<typename T>
	void DLL ForEach(std::vector<T> in, func_t _Run)
	{
		for (int i = 0; i < in.size(); i++)
		{
			_Run();
		}
	}
	template<typename T>
	bool DLL in_array(T* _array, T _is, size_t size)
	{
		bool no = false;
		for (int i = 0; i < size; i++)
		{
			if (_array[i] == _is)
			{
				return true;
			}
			else {
				no = true;
			}
		}
		if (no == true)
		{
			return false;
		}
	}
	template<typename T>
	bool DLL in_vector(std::vector<T> _array, T _is)
	{
		bool no = false;
		for (auto i : _array)
		{
			if (_array[i] == _is)
			{
				return true;
			}
			else {
				no = true;
			}
		}
		if (no == true)
		{
			return false;
		}
	}
	// Interupts the program so you can do something else
	void DLL Interrupt(void(Run)(void))
	{
		Run();
	}
	bool DLL canBeDividedBy(int num, int divisor)
	{
		int r = num % divisor;
		if (r == 0)
			return true;
		else
			return false;
	}
	bool DLL operator==(Port p1, Port p2)
	{
		return p1.m_Port == p2.m_Port;
	}
	RunOnDestruction::RunOnDestruction(std::function<func_t> Run)
	{
		this->Run = Run;
	}
	RunOnDestruction::RunOnDestruction(std::function<func_t> Run, std::function<func_t> RunOnConstruction)
	{
		this->Run = Run;
		RunOnConstruction();
	}
	RunOnDestruction::~RunOnDestruction()
	{
		Run();
	}
	NTFSads::NTFSads()
		:file(""), ADSName(""), isDefault(1)
	{
	}
	NTFSads::NTFSads(const char* file, const char* ADSName, std::ios_base::openmode _ModeO, int _Prot)
		: file(file), ADSName(ADSName), isDefault(0), _ModeO( _ModeO ), _Prot(_Prot)
	{
		std::string ads = this->file;
		ads.append(":");
		ads.append(this->ADSName);
		outADS.open(ads, _ModeO, _Prot);
		inADS.open(ads, std::ios_base::in);
	}
	void NTFSads::Tructuate()
	{
		std::string ads = this->file;
		ads.append(":");
		ads.append(this->ADSName);
		std::ofstream of(ads, std::ios::trunc);
		of.close();
	}
	NTFSads::~NTFSads()
	{
		if (!isDefault && !closed)
		{
			outADS.close();
			inADS.close();
			closed = true;
		}
	}
	bool NTFSads::isClosed()
	{
		return closed;
	}
	void NTFSads::open(const char* file, const char* ADSName, std::ios_base::openmode _ModeO, int _Prot)
	{
		if (isDefault && file != "" && ADSName != "")
		{
			this->_Prot = _Prot;
			this->_ModeO = _ModeO;
			this->file = file;
			this->ADSName = ADSName;
			std::string ads = this->file;
			ads.append(":");
			ads.append(this->ADSName);
			outADS.open(ads, _ModeO, _Prot);
			inADS.open(ads, std::ios_base::in);
		}
	}
	void NTFSads::DeleteADS()
	{
		if (!isClosed() && !deleted)
		{
			deleted = 1;
			std::string ads = file;
			ads.append(":");
			ads.append(ADSName);
			closed = 1;
			close();
			DeleteFileA(ads.c_str());
		}
	}
	bool NTFSads::SplitFileFromADS(const char* newFn)
	{
		if (newFn == file)
		{
			return false;
		}
		else {
			if (!isClosed() && !deleted)
			{
				std::string ads = file;
				ads.append(":");
				ads.append(ADSName);
				std::ifstream ifstr{ ads, std::ios_base::in };
				std::string filec{ std::istreambuf_iterator<char>{ ifstr }, {} };
				ifstr.close();
				closed = 1;
				close();
				std::ofstream of{ newFn, std::ios_base::trunc | std::ios_base::out };
				of << filec << std::flush;
				of.close();
				DeleteFileA(ads.c_str());
			}
		}
		return true;
	}
	bool NTFSads::MakeADS()
	{
		std::string ads = file;
		ads.append(":");
		ads.append(ADSName);
		if (outADS.is_open())
		{
			outADS.close();
			outADS.open(ads, _ModeO, _Prot);
			if(outADS.is_open())
				return true;
		}
		else
			return false;
	}
	std::string NTFSads::ReadADS()
	{
		std::string ads = file;
		ads.append(":");
		ads.append(ADSName);
		if (inADS.is_open())
		{
			std::ifstream ifstr{ ads };
			std::string filec{ std::istreambuf_iterator<char>{ ifstr }, {} };
			ifstr.close();
			return filec;
		}
		else
			return "[ERROR UTIL.DLL] Input Stream isn't open!";
	}
	bool NTFSads::WriteADS(std::string toWrite)
	{
		std::string ads = file;
		ads.append(":");
		ads.append(ADSName);
		if (!std::filesystem::exists(ads))
		{
			return false;
		}
		else
		{
			outADS << toWrite << std::flush;
		}
		return true;
	}
	void NTFSads::close()
	{
		closed = 1;
		outADS.close();
		inADS.close();
	}
	bool DLL CheckFileModification(std::string file, bool delay, time_t milliseconds, std::string format)
	{
#pragma warning(push )
#pragma warning(disable :4996)
		namespace fs = std::filesystem;
		namespace time = std::chrono;
		namespace thread = std::this_thread;
		if (delay)
			thread::sleep_for(time::milliseconds(milliseconds));
		bool end = false;
		while (!end)
		{
			fs::file_time_type file_time = fs::last_write_time(file);
			std::time_t tt = to_time_t(file_time);
			std::tm* gmt = std::gmtime(&tt);
			std::stringstream buffer;
			buffer << std::put_time(gmt, format.c_str());
			std::string formattedFileTime = buffer.str();

			auto t = std::time(nullptr);
			auto tm2 = *std::gmtime(&t);

			std::ostringstream oss;
			oss << std::put_time(&tm2, format.c_str());
			auto str = oss.str();
			if (formattedFileTime == str)
			{
				return true;
			}
		}
#pragma warning(pop)
	}
	bool DLL CheckFileModification(std::string file, bool delay, time_t milliseconds, bool reserved)
	{
		namespace time = std::chrono;
		namespace thread = std::this_thread;
		if(delay)
			thread::sleep_for(time::milliseconds(milliseconds));
		bool end = false;
		std::ifstream ifstr{};
		ifstr.open(file, std::ios_base::in || std::ios_base::binary);
		if (!ifstr.is_open())
		{
			return false;
		}
		std::string preFile(std::istreambuf_iterator<char>{ ifstr }, {});
		ifstr.close();
		while (!end)
		{
			ifstr.open(file, std::ios_base::in || std::ios_base::binary);
			std::string filecontents(std::istreambuf_iterator<char>{ ifstr }, {});
			if (preFile != filecontents)
			{
				return true;
			}
			ifstr.close();
		}
	}
	int GetFileSize(std::string fn)
	{
		std::ifstream in_file(fn, std::ios::binary);
		in_file.seekg(0, std::ios::end);
		return in_file.tellg();
	}
	void FindAndReplaceFile(const char* _fn, std::string toFind, std::string toReplace)
	{
		std::ifstream ifstr{ _fn };
		std::string file(std::istreambuf_iterator<char>{ ifstr }, {});
		size_t index = file.find(toFind);
		if (index == std::string::npos) {
			std::cerr << "Cannot find " << toFind << "!\n";
		}
		else
		{
			file.replace(index, toFind.size(), toReplace);
		}
		std::ofstream ofstr{ _fn };
		ofstr << file;
	}
	void DLL OutputAtCoordA(HANDLE _handle, DWORD _length, LPCSTR _str, COORD _pos, WORD _attrib)
	{
		DWORD _charWritten1;
		DWORD _charWritten2;
		WriteConsoleOutputCharacterA(_handle, _str, _length, _pos, &_charWritten1);
		WriteConsoleOutputAttribute(_handle, &_attrib, _length, _pos, &_charWritten2);
	}
	void DLL OutputAtCoordW(HANDLE _handle, DWORD _length, LPCWSTR _str, COORD _pos, WORD _attrib)
	{
		DWORD _charWritten1;
		DWORD _charWritten2;
		WriteConsoleOutputCharacterW(_handle, _str, _length, _pos, &_charWritten1);
		WriteConsoleOutputAttribute(_handle, &_attrib, _length, _pos, &_charWritten2);
	}
	bool DLL isEven(int _Num)
	{
		if (_Num % 2 == 0)
			return true;
		else
			return false;
	}
	
	// ---------------------------------------------------------------------------------------------------
	InternetServerTDP::InternetServerTDP(Port port)
		:m_Port(port)
	{
		m_IResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
		if (m_IResult != 0) {
			printf("WSAStartup failed with error: %d\n", m_IResult);
			return;
		}

		ZeroMemory(&m_Hints, sizeof(m_Hints));
		m_Hints.ai_family = AF_INET;
		m_Hints.ai_socktype = SOCK_STREAM;
		m_Hints.ai_protocol = IPPROTO_TCP;
		m_Hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		m_IResult = getaddrinfo(NULL, std::to_string(port.get_port()).c_str(), &m_Hints, &m_Result);
		if (m_IResult != 0) {
			printf("getaddrinfo failed with error: %d\n", m_IResult);
			WSACleanup();
			return;
		}

		m_ListenSocket = socket(m_Result->ai_family, m_Result->ai_socktype, m_Result->ai_protocol);
		if (m_ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(m_Result);
			WSACleanup();
			return;
		}

		// Setup the TCP listening socket
		m_IResult = bind(m_ListenSocket, m_Result->ai_addr, (int)m_Result->ai_addrlen);
		if (m_IResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(m_Result);
			closesocket(m_ListenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(m_Result);

		m_IResult = listen(m_ListenSocket, SOMAXCONN);
		if (m_IResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(m_ListenSocket);
			WSACleanup();
			return;
		}
	}

	InternetServerTDP::~InternetServerTDP()
	{
		CloseSocket();
		WSACleanup();
	}

	void InternetServerTDP::CloseSocket()
	{
		shutdown(m_ClientSocket, SD_SEND);
		closesocket(m_ClientSocket);
	}
	
	void InternetServerTDP::AcceptConnectionFromClient()
	{
		m_IResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
		if (m_IResult != 0) {
			printf("WSAStartup failed with error: %s\n", ErrorCodeToString(m_IResult).c_str());
			return;
		}
		m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
		if (m_ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %s\n", ErrorCodeToString(WSAGetLastError()).c_str());
			closesocket(m_ListenSocket);
			WSACleanup();
			return;
		}

		closesocket(m_ListenSocket);
	}

	void InternetServerTDP::SendMessageToClient(const char* message)
	{
		(void)WSAStartup(MAKEWORD(2, 2), &m_WsaData);
		m_ISendResult = send(m_ClientSocket, message, m_IResult, 0);
		if (m_ISendResult == SOCKET_ERROR) {
			printf("send failed with error: %s\n", ErrorCodeToString(WSAGetLastError()).c_str());
			closesocket(m_ClientSocket);
			WSACleanup();
			return;
		}
	}

	int InternetServerTDP::ReciveMessageFromClient()
	{
		(void)WSAStartup(MAKEWORD(2, 2), &m_WsaData);
		return recv(m_ClientSocket, m_Recvbuf, m_Recvbuflen, 0);
	}

	const char* InternetServerTDP::GetMessageFromBuffer()
	{
		return m_Recvbuf;
	}

	std::string InternetServerTDP::ErrorCodeToString(int ecode)
	{
		//Get the error message ID, if any.
		if (ecode == 0) {
			return std::string(); //No error message has been recorded
		}

		LPSTR messageBuffer = nullptr;

		//Ask Win32 to give us the string version of that message ID.
		//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ecode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		//Copy the error message into a std::string.
		std::string message(messageBuffer, size);

		//Free the Win32's string's buffer.
		LocalFree(messageBuffer);

		return message;
	}
	std::string ErrorCodeToString(int ecode)
	{
		//Get the error message ID, if any.
		if (ecode == 0) {
			return std::string(); //No error message has been recorded
		}

		LPSTR messageBuffer = nullptr;

		//Ask Win32 to give us the string version of that message ID.
		//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, ecode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		//Copy the error message into a std::string.
		std::string message(messageBuffer, size);

		//Free the Win32's string's buffer.
		LocalFree(messageBuffer);

		return message;
	}
	// ---------------------------------------------------------------------------------------------------
	bool Port::is_invalid() const
	{
		return m_Port < 65535 || m_Port > 0;
	}

	unsigned int Port::get_port() const
	{ return m_Port; }

	Port::Port(uint4_t port)
		:m_Port(port)
	{
		if (is_invalid())
		{
			m_Port = 1;
		}
	}
	// ---------------------------------------------------------------------------------------------------

	InternetClientTDP::InternetClientTDP(const char* name, Port tcp_port)
		:m_Name(name), m_TcpPort(tcp_port)
	{
		if (m_Name == "localhost")
			m_Name = "127.0.0.1";
		m_ECResult = WSAStartup(MAKEWORD(2, 2), &m_Wsa);
		if (m_ECResult > 0)
		{
			std::string msg = ErrorCodeToString(m_ECResult);
			LOG_ERROR(WSAStartup(), 591, msg);
			WSACleanup();
			m_State = false;
			return;
		}

		m_Socket = socket(
			AF_INET,
			SOCK_STREAM,
			IPPROTO_TCP);
		if (m_Socket == INVALID_SOCKET)
		{
			std::string msg = ErrorCodeToString(WSAGetLastError());
			LOG_ERROR(socket(), 600, msg);
			WSACleanup();
			m_State = false;
			return;
		}
		PRAGMA_WARNING_TEMP_DISABLE(4996)
		m_Server.sin_addr.s_addr = inet_addr(name);
#pragma warning(pop)
		m_Server.sin_family = AF_INET;
		m_Server.sin_port = htons(m_TcpPort.get_port());

		m_ECResult = connect(m_Socket, (const sockaddr*)&m_Server, sizeof(m_Server));
		int ec = WSAGetLastError();
		if (m_ECResult == SOCKET_ERROR) {
			CloseSocket();
			m_Socket = INVALID_SOCKET;
		}

		if (m_Socket == INVALID_SOCKET) {
			std::string msg = ErrorCodeToString(ec);
			LOG_ERROR(connect(), 617, msg);
			WSACleanup();
			m_State = false;
			return;
		}
	}

	InternetClientTDP::~InternetClientTDP()
	{
		CloseSocket();
		if(m_State)
			WSACleanup();
	}

	void InternetClientTDP::CloseSocket(IN_OPT shutdown_how how)
	{
		shutdown(m_Socket, (int)how);
		closesocket(m_Socket);
	}

	void InternetClientTDP::Send(IN const char* msg)
	{
		if (m_State)
		{
			if (send(
				m_Socket,
				msg,
				strlen(msg),
				NULL
			) == SOCKET_ERROR)
			{
				int ec = WSAGetLastError();
				std::string message = ErrorCodeToString(ec);
				LOG_ERROR(send(), 654, message);
			}
		}
	}

	int InternetClientTDP::Recive()
	{
		if(m_State)
			return recv(
				m_Socket,
				m_LastRetrievedMessage,
				5000,
				NULL
			);
		strcpy_s(m_LastRetrievedMessage, 15,"State is false");
		return -1;
	}

	const char* InternetClientTDP::GetRecivedMessageFromBuffer() const
	{
		return m_LastRetrievedMessage;
	}

	const char* InternetClientTDP::SendRecive(IN const char* msg)
	{
		Send(msg);
		Recive();
		return GetRecivedMessageFromBuffer();
	}
}