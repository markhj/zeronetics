@page arch-render-manager Control flow of rendering

This document details decision-making about the engine design.

## 🔀 Management of allocation

As you've probably read in @ref render-manager, the renderer
is responsible for managing requests. In theory, this means the
renderer could just discard the requests, or do the exact
opposite of what's requested. _In theory_.

But on the other hand it gives renderers the ability to manage
allocation, de-allocation and updates in a way which is
performance-wise optimal for the specific renderer.
Keep in mind that
renderers don't work the same way, and we should make as few
assumptions about renderers as possible, and especially about
_how_ they work. The more assumptions we make, the harder it is
to implement a new renderer in a way where it performs to its
absolute best.

The renderer can process requests at a time when it sees fit,
and in the order it desires.

> **Example**: You request a renderer to add object A and
> then delete object B.
> 
> If the render manager had authority over the strategy
> (which it doesn't), then the renderer would just have
> to execute these operations in the order it was instructed.
> 
> But in Zeronetics, the renderer has authority to decide
> how, when and why it processes requests.
> Let's say a hypothetical renderer figured out that
> by deleting B first, it can re-use the space in the buffer
> where B was to allocate A, avoiding costly buffer resizing.
> It would've been a shame to take away the freedom to do
> so from the renderer.
>
> _**Note: This is hypothetical scenario.**_

If the render manager had authority over the strategy,
then two render systems which work differently would
be forced to use identical strategies, making one or both
function in a suboptimal fashion.

To summarize, this decision is founded in a desire to provide
renderers with freedom and flexibility to manage allocation
in a way that's optimal for their specific implementation.
