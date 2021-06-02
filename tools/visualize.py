# %%
# This script creates a plot of the convex hulls listed in a JSON file, to help visualize

# %%
import json
from matplotlib import pyplot as plt

# %%
# colors = ['#%02x%02x%02x' % tuple(map(lambda x: int(x * 255), colorsys.hsv_to_rgb(i / 12.0, 0.5, 0.5))) for i in range(12)]
colors = ['#7f3f3f', '#7f5f3f', '#7f7f3f', '#5f7f3f', '#3f7f3f', '#3f7f5f',
          '#3f7f7f', '#3f5f7f', '#3f3f7f', '#5f3f7f', '#7f3f7f', '#7f3f5f']

# %%


def draw_polygon(ax, n, axpexes):
    x = [p["x"] for p in axpexes]
    x.append(x[0])
    y = [p["y"] for p in axpexes]
    y.append(y[0])

    ax.plot(x, y, label='{}'.format(n), color=colors[n])


# %%
fig, ax = plt.subplots()

with open("./convex_hulls.json") as file:
    for polygon in json.load(file)["convex hulls"]:
        draw_polygon(ax, polygon["ID"], polygon["apexes"])
    ax.set_title("PROBLEM")

ax.legend()
plt.show()

# %%
fig, ax = plt.subplots()

with open("./tools/expected_result_convex_hulls.json") as file:
    for polygon in json.load(file)["convex hulls"]:
        draw_polygon(ax, polygon["ID"], polygon["apexes"])
    ax.set_title("EXPECTED SOLUTION")

ax.legend()
plt.show()

# %%
fig, ax = plt.subplots()

with open("result_convex_hulls.json") as file:
    for polygon in json.load(file)["convex hulls"]:
        draw_polygon(ax, polygon["ID"], polygon["apexes"])
    ax.set_title("SOLUTION")

ax.legend()
plt.show()
