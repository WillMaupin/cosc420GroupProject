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

#Set a var to = total file frames/world size for dividing tasks with mpi
alloc = num_frames/size
stream.setpos(rank * int(alloc))

arr = [] 
count = 0

#Iterate through wav file reading 1 frame at a time. One frame consists of 2 channels in this case (stereo). Each node unpacks their own part of wav one at a time and loads mono data (average of stereo) into an array. 
while(stream.tell() < (rank+1) * int(alloc)):
	
	x = stream.readframes(1) 
	integer_data = struct.unpack("2h", x)
	y = integer_data[0];
	z = integer_data[1];
	arr.append((y + z)/2) 

stream.close()

#Gather arrays from all nodes into one single array
newarr = comm.gather(arr, root=0)

#Plot data 
if rank == 0:
	
	#arr = arr.mean(axis=1)
	plot.subplot(211)
	plot.title('Spectrogram of a wav file')
	plot.plot(arr)
	plot.xlabel('Sample')
	plot.ylabel('Amplitude')
	plot.subplot(212)
	plot.specgram(arr,Fs=44100)
	plot.xlabel('Time')
	plot.ylabel('Frequency')
	plot.ylim((0, 15000))

MPI.Finalize()
plot.show()

