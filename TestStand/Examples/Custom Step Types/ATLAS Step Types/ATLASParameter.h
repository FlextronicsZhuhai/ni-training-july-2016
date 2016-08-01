#ifndef __ATLAS_PARAMETER_H_
#define __ATLAS_PARAMETER_H_

typedef enum {
    Number  = 0, 
    String  = 1, 
    Boolean = 2
} ValueTypes;

typedef enum {
    Read            = 0, 
    Write           = 1, 
    ReadWrite   = 2
} PassModes;

class CATLASParameter
{
public:
    CATLASParameter() : 
        m_ValueType(Number), 
        m_PassMode(Read), 
        m_IsGlobalVariable(true)
    {}

    CString m_Name;
    ValueTypes m_ValueType;
    PassModes m_PassMode;
    BOOL m_IsGlobalVariable;
    CString m_ValueExpression;
};

typedef CTypedPtrArray<CPtrArray, CATLASParameter*> CATLASParameterArray;

class CATLASParameters
{
public:
    ~CATLASParameters()
    {
        for (int i = 0; i < m_Parameters.GetSize(); i++)
            delete m_Parameters[i];
        m_Parameters.RemoveAll();
    }
    CATLASParameterArray m_Parameters;
};

#endif //__ATLAS_PARAMETER_H_
