import wave
import matplotlib.pyplot as plot
import struct
from mpi4py import MPI
from scipy.io import wavfile

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

stream = wave.open("cosc420.wav", 'rb')

#Get wav file metadata
num_channels = stream.getnchannels()
sample_rate = stream.getframerate()
sample_width = stream.getsampwidth()
num_frames = stream.getnframes()
total_samples = num_frames*num_channels

#check sample type for stereo or mono to read data accordingly
if sample_width == 1: 
	fmt = "1B" 
elif sample_width == 2:
	fmt = "2h" 
else:
        raise ValueError("Only supports 8 and 16 bit audio formats.")

#Set a var to = total file frames/world size for dividing tasks with mpi
alloc = num_frames/size
stream.setpos(rank * int(alloc))

arr = [] 
count = 0

#Iterate through wav file reading 1 frame at a time. One frame consists of 2 channels in this case (stereo). Each node unpacks their own part of wav one at a time and loads mono data (average of stereo) into an array. 
while(stream.tell() < (rank+1) * int(alloc)):
	
	x = stream.readframes(1) 
	integer_data = struct.unpack(fmt, x)
	y = integer_data[0];
	z = integer_data[1];
	arr.append((y + z)/2) 

stream.close()

#newarr = []

#Gather arrays from all nodes into one single array
arr = comm.gather(arr, root=0)
newarr = []
if rank==0:
	for i in range(0,size):
		for j in range(0, int(alloc)):
			newarr.append(arr[i][j])

'''for i in newarr:
	print(newarr)
	print(arr)
	time.sleep(1)'''

#Plot data 
if rank == 0:
	#arr = arr.mean(axis=1)
	plot.subplot(211)
	plot.title('Spectrogram of a wav file')
	plot.plot(newarr)
	plot.xlabel('Sample')
	plot.ylabel('Amplitude')
	plot.subplot(212)
	plot.specgram(newarr,Fs=44100)
	plot.xlabel('Time')
	plot.ylabel('Frequency')
	plot.ylim((0, 15000))

MPI.Finalize()
plot.show()

