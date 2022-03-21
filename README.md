# Sample : Edvice on Azure Sphere

This sample shows Edvice integration into the Microsoft Azure Sphere real-time core (cortex-m4) are able to run together on MT3620 Development Kit. This sample runs edvice inference model on [Azure RTOS](https://azure.com/rtos) 

To clone this repository, you can use this command.

```bash
git clone --recursive git@github.com:ENERZAi/ZaiOptimizer.git
```

## Prepare your device

Please go to this page and follow the instructions to setup the Azure sphere SDK and device before running this sample
[Azure Sphere Quickstart](https://docs.microsoft.com/en-us/azure-sphere/install/install-sdk?pivots=visual-studio)

## Build and run the sample

1. Under the AzSphereEdvice repository, create lib_arm folder
2. Place libModel.a file downloaded from edvice website under AzSphereEdvice/lib_arm directory 
   __(Note : Model is required to be trained in soft float-abi mode)__
3. Place Edvice.h file downloaded from edvice website under AzSphereEdvice/Includes directory (If it already exists, replace it)
4. Open Visual Studio with Azure Sphere SDK installed and run CMake
5. Build and run the example on your Azure Sphere device

> Note: You need Azure Sphere SDK version >= 20.07 to build and run the sample.

## How to connect BMI160 Accelerometer/Gyroscope to Azure sphere
BMI160 SCL <-> Azure Sphere SCL
BMI160 SDA <-> Azure Sphere SDA
BMI160 Vin (+) <-> Azure Sphere 5v
BMI160 GND (-) <-> Azure Sphere GND

## LED state indicator
User LED on Azure Sphere will give you the inference result or indicate error state
* Blue -> Abnormal
* Green -> Normal
* Red -> Error (Most likely to be caused by sensor malfunction. Try reconnecting the sensor or reboot the Azure sphere)

## Set up hardware to display output

To prepare your hardware to display output from the sample:

1. Attach the USB-to-serial adapter to your PC.
2. Open serial monitor (Putty in case of windows) and choose the right COM port that your device is conected to
3. Serial monitor will display state to the user -> It will print inference result as "Normal" or "Abnormal" 

## Contributions

Project Edvice belongs to Enerzai corporation ([New tab (enerzai.com)](http://www.enerzai.com/))

This project is based on this repository 

(git@github.com:Azure-Samples/Azure-RTOS-on-Azure-Sphere-Mediatek-MT3620.git)

