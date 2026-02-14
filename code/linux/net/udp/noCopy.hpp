class noCopy
{
public:    
    noCopy()
    {
        
    }

    noCopy(const noCopy&) = delete;
    noCopy& operator=(const noCopy&) = delete;

    ~noCopy()
    {
        
    }
};
