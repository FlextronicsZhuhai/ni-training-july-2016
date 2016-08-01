
Benchmarkps.dll: dlldata.obj Benchmark_p.obj Benchmark_i.obj
	link /dll /out:Benchmarkps.dll /def:Benchmarkps.def /entry:DllMain dlldata.obj Benchmark_p.obj Benchmark_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Benchmarkps.dll
	@del Benchmarkps.lib
	@del Benchmarkps.exp
	@del dlldata.obj
	@del Benchmark_p.obj
	@del Benchmark_i.obj
