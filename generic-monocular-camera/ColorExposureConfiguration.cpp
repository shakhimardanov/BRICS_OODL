#include "ColorExposureConfiguration.hpp"




ColorExposureConfiguration::ColorExposureConfiguration(): deviceColorExposureDev(NULL), handleColorExposureDev(NULL),
                                                          colorConfPropertyCounter(0), returnStatus(STATUS_FAILURE)
{
    std::cout << "Creating ColorExposureConfiguration without arguments" << std::endl;

}


ColorExposureConfiguration::ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle): deviceColorExposureDev(device),
                                                                                                          handleColorExposureDev (handle),
                                                                                                          colorConfPropertyCounter(0),
                                                                                                          returnStatus(STATUS_FAILURE)
{
    std::cout << "Creating ColorExposureConfiguration with arguments" << std::endl;

}


ColorExposureConfiguration::ColorExposureConfiguration(ColorExposureConfiguration &colorconfig)
{


}

ColorExposureConfiguration& ColorExposureConfiguration::operator=(ColorExposureConfiguration &colorconfig)
{
    if(&colorconfig != this)
    {
        std::cout << "Inside ColorExposureConfiguration assignment" <<std::endl;
    }

    return *this;
}


ColorExposureConfiguration::~ColorExposureConfiguration() 
{
    std::cout << "Destroying ColorExposureConfiguration with arguments" << std::endl;

}


bool ColorExposureConfiguration::getListOfColorProperties() 
{
    std::cout << "Inside ColorExposureConfiguration getListOfColorProperties" << std::endl;
    int returnValue = 0;
    //number of properties allocated is 30 for now, change it to const or make it dynamic
    for( int propertyCounter = 0; propertyCounter < 30 ; propertyCounter++ ) 
    {
        returnValue = unicap_enumerate_properties( *handleColorExposureDev, NULL, &listOfProperties[propertyCounter], 
                                                   propertyCounter);
        if( SUCCESS(returnValue) )
        {
            std::cout << listOfProperties[propertyCounter].identifier<<std::endl;
            colorConfPropertyCounter++;
            returnStatus = STATUS_SUCCESS;
        }
        else
            break;

    }

    if(listOfProperties != NULL )
    {
        std::cout << "Number of properties " << colorConfPropertyCounter<<std::endl;
        return true;
    }
    else
    {
        std::cout << "Property list is empty"<<std::endl;
        return false;
    }
 
}

bool ColorExposureConfiguration::getHueValue(double &hue) 
{
    std::cout << "Inside ColorExposureConfiguration getHueValue" << std::endl;
    const std::string propertyName ="hue";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        hue = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            hue = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}


bool ColorExposureConfiguration::getContrastValue(double &contrast) 
{
   std::cout << "Inside ColorExposureConfiguration getContrastValue" << std::endl;
    const std::string propertyName ="contrast";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        contrast = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            contrast = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}


bool ColorExposureConfiguration::getSaturationValue(double &saturation) 
{
   std::cout << "Inside ColorExposureConfiguration getSaturationValue" << std::endl;
    const std::string propertyName ="saturation";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        saturation = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            saturation = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}


bool ColorExposureConfiguration::getWhiteBalanceUValue(double &uValue) 
{
   std::cout << "Inside ColorExposureConfiguration getWhiteBalanceUValue" << std::endl;
    const std::string propertyName ="white_balance_u";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        uValue = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            uValue = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}


bool ColorExposureConfiguration::getWhiteBalanceVValue(double &vValue) 
{
   std::cout << "Inside ColorExposureConfiguration getWhiteBalanceVValue" << std::endl;
    const std::string propertyName ="white_balance_v";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        vValue = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            vValue = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}


bool ColorExposureConfiguration::getBrightnessValue(double &brightness) 
{
   std::cout << "Inside ColorExposureConfiguration getBrightnessValue" << std::endl;
    const std::string propertyName ="brightness";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        brightness = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            brightness = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}


bool ColorExposureConfiguration::getGainControlValue(double &gain) 
{
   std::cout << "Inside ColorExposureConfiguration getGainControlValue" << std::endl;
    const std::string propertyName ="gain";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        gain = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            gain = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}



bool ColorExposureConfiguration::getShutterTime(double &sTime) 
{
   std::cout << "Inside ColorExposureConfiguration getShutterTime" << std::endl;
    const std::string propertyName ="shutter";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        sTime = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            sTime = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}



bool ColorExposureConfiguration::getExposureTime(double &eTime) {

}


bool ColorExposureConfiguration::getColorTemperatureValue(double &temp) 
{
   std::cout << "Inside ColorExposureConfiguration getColorTemperatureValue" << std::endl;
    const std::string propertyName ="temperature";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if (charID == propertyName)
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        temp = listOfProperties[propertyCounter].value;
                        //   std::cout << rate << std::endl;
                        return true;
                    }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            temp = listOfProperties[propertyCounter].value;
                            return true;
                        }
                    }
                }
                //if property is not of type "range" go to the beginning of the loop
            }
        }
        else
        {
            std::cout << "Property list is empty"<< std::endl;
            return false;
        }
    }
}




bool ColorExposureConfiguration::setHueValue(double &hue) {

}

bool ColorExposureConfiguration::setChromaValue(double &chroma) {

}

bool ColorExposureConfiguration::setSaturationValue(double &saturation) {

}


bool ColorExposureConfiguration::setWhiteBalanceUValue(double &uValue) {

}

bool ColorExposureConfiguration::setWhiteBalanceVValue(double &vValue) {

}

bool ColorExposureConfiguration::setBrightnessValue(double &brightness) {

}

bool ColorExposureConfiguration::setGainControlValue(double &gain) {

}

bool ColorExposureConfiguration::setShutterTime(double &sTime) {

}

bool ColorExposureConfiguration::setExposureTime(double &eTime) {

}

bool ColorExposureConfiguration::setColorTemperatureValue(double &temp) {

}
