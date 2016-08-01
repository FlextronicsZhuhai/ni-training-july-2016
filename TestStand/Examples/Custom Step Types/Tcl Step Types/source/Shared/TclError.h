#if !defined(_TCL_ERROR_H_)
#define _TCL_ERROR_H_

struct TclError
{
	HRESULT error;
	_bstr_t description;

	TclError()
	{
		error = S_OK;
		description = L"";
	}

	TclError(const TclError& err)
	{
		error = err.error;
		description = err.description;
	}

	TclError(HRESULT result, _bstr_t& desc)
	{
		error = result;
		description = desc;
	}
	TclError(_com_error& err)
	{
		(*this) = err;
	}
	TclError& operator = (_com_error& err)
	{
		error = err.Error();
		description = err.Description();
		return (*this);
	}
	operator bool() {
		return bool(error != S_OK);
	} 
};
#endif