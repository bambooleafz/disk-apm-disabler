## usage

Disable physical drive 0, 1 and 3:

```
apmdisable.exe 0 1 3
```

The physical drive number can be simply obtained from `disk management` utility of Windows

## Notice

- Currently only available on Windows

- Currently only available on ATA devices, i.e. it might not work on some USB drives

- Your disk needs to support at least ATA5, or ACS-2 standard. But don't worry about that 'cause modern HDDs always support them
