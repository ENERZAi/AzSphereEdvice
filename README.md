# Edvice on Azure Sphere

This sample shows Edvice integration into the Microsoft Azure Sphere real-time core (cortex-m4) [Azure RTOS](https://azure.com/rtos) are able to run together on MT3620 Development Kit.

To clone this repository, you can use this command.

```bash
git clone --recursive git@github.com:ENERZAi/ZaiOptimizer.git
```

## Prepare your device

To prepare your device on Windows:

1. Right-click the Azure Sphere Developer Command Prompt shortcut and select **More>Run as administrator**.

   The [`--enable-rt-core-debugging`](https://docs.microsoft.com/azure-sphere/app-development/build-rt-app?tabs=windows%2Ccliv2beta&pivots=visual-studio#enable-development-and-debugging) parameter requires administrator privilege because it installs USB drivers for the debugger.

1. Enter the following azsphere command:

   ```cmd
   azsphere device enable-development --enable-rt-core-debugging
   ```

1. Close the window after the command completes because administrator privilege is no longer required. As a best practice, you should always use the lowest privilege that can accomplish a task.

To prepare your device on Linux:

1. Enter the following azsphere command:

   ```cmd
   azsphere device enable-development --enable-rt-core-debugging
   ```

You may need to update the OS by using if you have an older device.

```cmd
azsphere device recover
```

## Set up hardware to display output

To prepare your hardware to display output from the sample:

1. Attach the USB-to-serial adapter to your PC.
1. Open serial monitor (Putty in case of windows)
1. Serial monitor will display state to the user

## Build and run the sample

1. Under the AzSphereEdvice repository, create lib_arm folder
2. Place libModel.a file downloaded from edvice website under AzSphereEdvice/lib_arm directory
3. Place Edvice.h file downloaded from edvice website under AzSphereEdvice/Includes directory (If it already exists, replace it)
4. Open Visual Studio with Azure Sphere SDK installed and run CMake
5. Build and run the example on your Azure Sphere device

> Note: You need Azure Sphere SDK version >= 20.07 to build and run the sample.

## Contributions

Project Edvice belongs to Enerzai corporation ([New tab (enerzai.com)](http://www.enerzai.com/))

This project is based on this repository 

(git@github.com:Azure-Samples/Azure-RTOS-on-Azure-Sphere-Mediatek-MT3620.git)

