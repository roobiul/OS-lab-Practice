n = int(input("Enter number of processes: "))

BT = []
TAT = [0] * n
WT = [0] * n
gantt = []

# Input Burst Times Only
for i in range(n):
    bt = int(input(f"Enter BT for P{i+1}: "))
    BT.append(bt)

current = 0

# FCFS order: P1, P2, P3...
for p in range(n):
    gantt.append(f"P{p+1}")
    current += BT[p]

    TAT[p] = current           # Turnaround = finish time
    WT[p] = TAT[p] - BT[p]     # Waiting = TAT - burst

# Print Gantt Chart
print("\nGantt Chart:")
print(" -> ".join(gantt))

# Average Times
AWT = sum(WT) / n
ATT = sum(TAT) / n

print("\nProcess\tBurst\tWaiting\tTurnaround")
for i in range(n):
    print(f"P{i+1}\t{BT[i]}\t{WT[i]}\t{TAT[i]}")

print(f"\nAverage Waiting Time: {AWT:.2f}")
print(f"Average Turnaround Time: {ATT:.2f}")
