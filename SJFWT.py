n = int(input("Enter number of processes: "))

BT = []
WT = [0] * n
TAT = [0] * n
gantt = []
current = 0

# Input only Burst Time
for i in range(n):
    bt = int(input(f"Enter Burst time for P{i}: "))
    BT.append(bt)

# Process list
process = list(range(n))

# SJF: always pick shortest BT from the remaining
while process:
    # pick process with shortest burst time
    p = min(process, key=lambda x: BT[x])
    
    gantt.append(f"P{p}")
    
    current += BT[p]
    TAT[p] = current          # since AT = 0
    WT[p] = TAT[p] - BT[p]
    
    process.remove(p)

# Output Gantt chart
print("\nGantt Chart:")
print(" -> ".join(gantt))

# Compute averages
AWT = sum(WT) / n
ATT = sum(TAT) / n

# Table output
print("\nProcess\tBurst\tWaiting\tTurnaround")
for i in range(n):
    print(f"P{i}\t{BT[i]}\t{WT[i]}\t{TAT[i]}")

print(f"\nAverage Waiting Time (AWT): {AWT:.2f}")
print(f"Average Turnaround Time (ATT): {ATT:.2f}")
