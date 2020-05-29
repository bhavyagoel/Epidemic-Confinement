# Epidemic-Confinement
To find minimum possible danger area which we need to confine to avoid further outbreak of disease with the help of CONVEX HULL.
### Introduction

During the 1770s, smallpox killed at least 30% of the West Coast Native Americans. The smallpox epidemic
of 1780-1782 brought devastation and drastic depopulation among the plains Indians.
And year 2020, we encountered another devastating pandemic namely COVID-19 by the deadly virus
Coronavirus, this virus is also as capable as smallpox in devastation and drastic depopulation across the
globe. This strain of virus is even more contagious than smallpox. It spreads with cough or sneeze as droplets
from mouth and nose to other people.
So, in order to tackle such an epidemic, we plot a graph with marking of most recent outburst of the disease,
which we assume to be the hospitals to mark record number of cases. By using the fact that approx. 5 km of
the outburst is the saturated area by virus. So, if the virus spreads uniformly in all directions, so it will form a
circle which we will say DANGER AREA (which we will represent by user specified count of coordinates on
these circles, all of which will be at an angle of 360 / (user specified count) degree with each other).
Suppose a place where happens to be recorded many such cases of disease, in which danger area may or
may not intersect the danger area caused by any other outbreak. So, we will end up having an intersection of
circles i.e. bunch of points, those intersection points are points that engulf both the circles.
We will find the minimum number of points which will cover the whole bunch of points inside it, when joined
with straight line. And those minimum points will not be anything but the boundary line of the danger area.
So, in this project we will be finding out the boundary line of the final intersected DANGER AREA with the help
of CONVEX HULL.

#### Algorithms used: -
  1. Jarvis March Algorithm
  2. Graham Scan Algorithm

#### Key Features:
  1. Marking the area to be kept under strict surveillance, to prevent further outbreak
  2. Graphical representation of the resulting area
  3. Calculating the area to be kept under surveillance
