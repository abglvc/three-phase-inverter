import matplotlib.pyplot as plt
import numpy as np

t = np.linspace(0, 0.02, 1000000)
sin_t = np.sin(2*np.pi*50*t)
sin_t_120 = np.sin(2*np.pi*50*t + 120/360 * 2*np.pi)
sin_t_240 = np.sin(2*np.pi*50*t + 240/360 * 2*np.pi)
zigzag_t = (2/np.pi*np.arccos(np.cos(2*np.pi*1000*t))-1)

plt.plot(t,sin_t,t,zigzag_t)
plt.show()

spwm_t = []
for i in range(len(sin_t)):
	if sin_t[i] >= zigzag_t[i]:
		spwm_t.append(1)
	else:
		spwm_t.append(0)

spwm_t_120 = []
for i in range(len(sin_t_120)):
	if sin_t_120[i] >= zigzag_t[i]:
		spwm_t_120.append(1)
	else:
		spwm_t_120.append(0)

spwm_t_240 = []
for i in range(len(sin_t_240)):
	if sin_t_240[i] >= zigzag_t[i]:
		spwm_t_240.append(1)
	else:
		spwm_t_240.append(0)

plt.plot(t,sin_t,t,zigzag_t,t,spwm_t)
plt.show()
plt.plot(t,sin_t_120,t,zigzag_t,t,spwm_t_120)
plt.show()
plt.plot(t,sin_t_240,t,zigzag_t,t,spwm_t_240)
plt.show()

plt.plot(t,spwm_t, 'r', t,spwm_t_120, 'g', t,spwm_t_240, 'b')
plt.show()

v_spwm_t = []
for i in range(len(t)):
	if i!=0 and spwm_t[i]!=spwm_t[i-1]:
		v_spwm_t.append(int(round(1000000*t[i])))

v_spwm_t_120 = []
for i in range(len(t)):
	if i!=0 and spwm_t_120[i]!=spwm_t_120[i-1]:
		v_spwm_t_120.append(int(round(1000000*t[i])))

v_spwm_t_240 = []
for i in range(len(t)):
	if i!=0 and spwm_t_240[i]!=spwm_t_240[i-1]:
		v_spwm_t_240.append(int(round(1000000*t[i])))

K = []
for v in v_spwm_t: K.append({'vrijeme':v, 'faza':1})
for v in v_spwm_t_120: K.append({'vrijeme':v, 'faza':2})
for v in v_spwm_t_240: K.append({'vrijeme':v, 'faza':3})

#sortiramo po vremenu sve pajpove
K.sort(key=(lambda k: k['vrijeme']))
#print(K)

D = [[(K[i]['vrijeme']-(K[i-1]['vrijeme'] if i!=0 else 0)), K[i]['faza']]
     for i in range(len(K))]
D.append([round(1000000*0.02)-K[-1]['vrijeme'], 0])
#zadnji wait ali bez promjene ikakve jer mora lijepo nastaviti novi ciklus
strD = str(D)

print(strD.replace('[','{').replace(']','}'))
print(len(D))
