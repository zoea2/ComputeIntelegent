#!/bin/bash

#!/bin/bash

#!/bin/bash
echo MBCDE
./MBCDE
if [ $? -eq 0 ]
then
	echo MBCDE successed
else
	echo MBCDE failed
fi
echo MBOCDE
./MBOCDE
if [ $? -eq 0 ]
then
	echo MBOCDE successed
else
	echo MBOCDE failed
fi
echo MRCDE
./MRCDE
if [ $? -eq 0 ]
then
	echo MRCDE successed
else
	echo MRCDE failed
fi
echo MROCDE
./MROCDE
if [ $? -eq 0 ]
then
	echo MROCDE successed
else
	echo MROCDE failed
fi


echo OMBCDE
./OMBCDE
if [ $? -eq 0 ]
then
	echo OMBCDE successed
else
	echo OMBCDE failed
fi
echo OMBOCDE
./OMBOCDE
if [ $? -eq 0 ]
then
	echo OMBOCDE successed
else
	echo OMBOCDE failed
fi
echo MRMBCDE
./MRMBCDE
if [ $? -eq 0 ]
then
	echo MRMBCDE successed
else
	echo MRMBCDE failed
fi
./MROMBCDE
if [ $? -eq 0 ]
then
	echo MROMBCDE successed
else
	echo MROMBCDE failed
fi
