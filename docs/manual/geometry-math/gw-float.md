@page gw-float Game world floating-point type

The ``ZEN::gw_float`` is a **floating-pointer type** ``typedef``
used for coordinates, and many factors which affect coordinates,
in the **game world**.

In large worlds, "wobbly" or "flickering" pixels can occur in the distance,
and that can often be solved with higher precision floating-point types.
But that comes at the cost of higher memory usage.

@note For the time being, ``gw_float`` is fixed to the regular ``float``.
But it was introduced for future-proofing, and should be in used in place
of ``float`` for properties and factors which are relevant to coordinates
in the game world.
