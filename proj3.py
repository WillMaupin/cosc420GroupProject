import wave
import matplotlib.pyplot as plot
import struct
from mpi4py import MPI
from scipy.io import wavfile

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

stream = wave.open("cosc420.wav", 'rb')

num_channels = stream.getnchannels()
sample_rate = stream.getframerate()
sample_width = stream.getsampwidth()
num_frames = stream.getnframes()
total_samples = num_frames*num_channels

alloc = num_frames/size
stream.setpos(rank * int(alloc))

arr = [0] * int(alloc)
count = 0

while(stream.tell() < (rank+1) * int(alloc)):
	
	x = stream.readframes(1)
	integer_data = struct.unpack("2h", x)
	y = integer_data[0];
	z = integer_data[1];
	arr[count] = int((y + z)/2)
	
	
	#print('rank',rank,'inserting',arr[count])
	count+=1

stream.close()
newarr = comm.gather(arr, root=0)

i=0
'''while i< len(arr):
	print(arr[i])
	print(newarr[i])
	print('\n')'''
#samplingFrequency, signalData = wavfile.read('cosc420.wav')
#signalData = signalData.mean(axis=1)
#print(newarr)
if rank == 0:
	#arr = arr.mean(axis=1)
	plot.subplot(211)
	plot.title('Spectrogram of a wav file')
	plot.plot(arr)
	plot.xlabel('Sample')
	plot.ylabel('Amplitude')
	#plot.subplot(212)
	#plot.specgram(arr,44100)
	#plot.xlabel('Time')
	#plot.ylabel('Frequency')

MPI.Finalize()
plot.show()
