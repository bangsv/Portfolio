import math
import time
from matplotlib import pyplot as plt
import dsmltf
from colorama import Fore, Style

dt = 2 * math.pi / 1000
result_of_om1 = math.pi / dt / 500
a0, a1, a2, b1, b2, om1, om2 = 0, 0, 0, -1.1, -1.1, math.pi / dt / 500,0
a = [a0,a1,a2,b1,b2,om1,om2]

def ex_1(k = 7):
    L = k / 50
    omega = 1000 / k
    data = [0, (-1) ** k * dt]

    for i in range(2, 500):
        data.append(data[-1] * (2 + dt * L * (1 - data[-2] ** 2)) - data[-2] * (1 + dt ** 2 + dt * L * (1 - data[-2] ** 2)) +
                dt ** 2 * math.sin(omega * i * dt))
   
    print(f'{Fore.GREEN}Ex_1:  Task completed', Style.RESET_ALL)
    return data 

def fx(i,a):
    a0, a1, a2, b1, b2, om1, om2 = tuple(a)
    return a0 + a1*math.cos(om1*i*dt) + b1*math.sin(om1*i*dt) + a2*math.cos(om2*i*dt) + b2*math.sin(om2*i*dt)

def F(a):
    return sum((fx(i,a)-x[i])**2 for i in range(500))

def ex_2():
    start = time.time()
    value = dsmltf.gradient_descent(F,a,500,0.001,0.002,1e-6)
    end = time.time()

    a_grag = tuple(value[0])

    plt.plot(range(500), x)
    plt.plot(range(500),[fx(i,a_grag) for i in range(500)], color="r")
    plt.title("Gradient descent")
    plt.show()

    print("\nEX_2_VALUE: ", value)
    print(f'{Fore.CYAN}Ex_2_TIME: {end - start} sec', Style.RESET_ALL)

def ex_3(): 
    start = time.time()
    value  = dsmltf.minimize_stochastic(fx, range(len(x)), x, a)
    end = time.time()

    a_stoch = tuple(value[0])

    plt.plot(range(500), x)
    plt.plot(range(500),[fx(i,a_stoch) for i in range(500)], color="r")
    plt.title("Stochastic gradient descent")
    plt.show()

    print("\nEx_3_VALUE: ",value)
    print(f'{Fore.CYAN}Ex_3_TIME: {end - start} sec', Style.RESET_ALL)

if __name__ == '__main__':
    
    x = ex_1(7)
    
    plt.plot(x)
    plt.title("Our x")
    plt.show()
    
    grafik = [fx(i,a) for i in range(500)]
    plt.plot(range(500), x)
    plt.plot(grafik, color="r")
    plt.title("Initial schedule")
    plt.show()
    
    ex_2()
    ex_3()


