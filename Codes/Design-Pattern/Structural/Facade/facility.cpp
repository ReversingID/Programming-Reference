/*
    Facade (Example)
    Archive of Reversing.ID
    Design Pattern (Structural)

Compile:
    [gcc]
    $ g++ facility.cpp -o facility

    [msvc]
    $ cl facility.cpp

Run:
    $ facility
*/
#include <iostream>


/* *********************************** DECLARATION *********************************** */
/**
 * MisDepartment (concrete) 
 * 
 * 
 */
class MisDepartment
{
    enum States
    {
        Received,           DenyAllKnowledge,   ReferClientToFacilities,
        FacilitiesHasNotSentPaperwork,          ElectricianIsNotDone,
        ElectricianDidItWrong,                  DispatchTechnician, 
        SignedOff,          DoesNotWork,        FixElectriciansWiring, 
        Complete
    };
    int _state;

public:
    void submitNetworkRequest()
    {
        _state = 0;
    }

    bool checkOnStatus()
    {
        _state++;

        if (_state == Complete)
            return true;

        return false;
    }
};

// ======================================================================================

/**
 * ElectricianUnion (concrete) 
 * 
 * 
 */
class ElectricianUnion
{
    enum States
    {
        Received,       RejectTheForm,          SizeTheJob,         SmokeAndJokeBreak,
        WaitForAuthorization, DoTheWrongJob,    BlameTheEngineer,   WaitToPunchOut,
        DoHalfAJob,     ComplainToEngineer,     GetClarification,   CompleteTheJob,
        TurnInThePaperwork, 
        Complete
    };
    int _state;

public:
    void submitNetworkRequest()
    {
        _state = 0;
    }

    bool checkOnStatus()
    {
        _state++;

        if (_state == Complete)
            return true;

        return false;
    }
};

// ======================================================================================

/**
 * FacilitiesDepartment (concrete) 
 * 
 * 
 */
class FacilitiesDepartment
{
    enum States
    {
        Received, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
          EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
          ReassignEngineer, EngineerReturns, EngineerResearchesAgain,
          EngineerFillsOutPaperWork, Complete
    };
    int _state;

public:
    void submitNetworkRequest()
    {
        _state = 0;
    }
    bool checkOnStatus()
    {
        _state++;

        if (_state == Complete)
            return true;

        return false;
    }
};

// ======================================================================================

/**
 * FacilitiesFacade (concrete) 
 * 
 * 
 */
class FacilitiesFacade
{
    enum States
    {
        Received,               SubmitToEngineer, 
        SubmitToElectrician,    SubmitToTechnician
    };
    int _state;
    int _count;

    // Sub System
    FacilitiesDepartment _engineer;
    ElectricianUnion _electrician;
    MisDepartment _technician;

public:
    FacilitiesFacade()
    {
        _count = 0;
    }

    void submitNetworkRequest()
    {
        _state = 0;
    }

    bool checkOnStatus()
    {
        _count++;

        /* Job request telah diterima */
        if (_state == Received)
        {
            _state++;

            /* Forward ke engineer */
            _engineer.submitNetworkRequest();
            std::cout << "submitted to Facilities - " << _count 
                      << " phone calls so far" << std::endl;
        }
        else if (_state == SubmitToEngineer)
        {
            /* Jika engineer sudah menyelesaikan tugas, forward ke electrician */
            if (_engineer.checkOnStatus())
            {
                _state++;

                _electrician.submitNetworkRequest();
                std::cout << "submitted to Electrician - " << _count 
                          << " phone calls so far" << std::endl;
            }
        }
        else if (_state == SubmitToElectrician)
        {
            /* Jika electrician sudah menyelesaikan tugas, forward ke technician */
            if (_electrician.checkOnStatus())
            {
                _state++;

                _technician.submitNetworkRequest();
                std::cout << "submitted to MIS - " << _count 
                          << " phone calls so far" << std::endl;
            }
        }
        else if (_state == SubmitToTechnician)
        {
            /* Jika technician sudah menyelesaikan tugas, proses secara keseluruhan telah selesai */
            if (_technician.checkOnStatus())
                return true;
        }
        
        return false;
    }

    int getNumberOfCalls()

    {
        return _count;
    }
};


/* *********************************** USAGE *********************************** */

int main()
{
    // Instansiasi facade
    FacilitiesFacade facilities;

    // Operasi terlihat terjadi di satu tempat, facademenangani banyak subsystem
    // secara bersamaan
    facilities.submitNetworkRequest();

    /* Keep checking until job is complete */
    while (!facilities.checkOnStatus());

    std::cout << "job completed after only " 
              << facilities.getNumberOfCalls() 
              << " phone calls" 
              << std::endl;
}