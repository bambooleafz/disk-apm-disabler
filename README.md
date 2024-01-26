# disk-apm-disabler

## introduction

This tool helps you disbale the APM(Advanced Power Management) function of your HDD

currently only available on windows

## usage

for example, you can disable apm function of physical drive 0, 1 and 3 using this command:
```
apmdisable.exe 0 1 3
```

you can simply obtain the drive number from `disk management` utility provided by windows

## notice

- this program works on ATA devices only; it might not work on sone USB drives

- currently, most ATA devices `should` support for `disabling APM`, as long as your disk supports ATA5/6/7/8 or ACS2/3/4/5
