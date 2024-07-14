@page entity-system Entity system

**Entities** make one of the most important concepts of Zeronetics.
Pretty much everything you will be coding on, interacting with,
and make your game world move and function, come back to entities.

In this article, we will take a brief helicopter-perspective look
at what entities are.

## ⚡ What are entities?

An entity is "anything" &mdash; or, almost anything &mdash; which can
be added to your game world. It doesn't have to be visible.
Cameras, timers and collision shapes are examples of entities which
cannot be _seen_, but still play an active role in the game.

## 🎁 How it works

Every entity comes back to ZEN::Entity. But from this point and
forward entities branch into many different categories and classes,
forming a hierarchy that includes anything from cameras, over lights,
to 3D models.

### Important entities

There are many important and useful entities, but some you'll
use in almost any project are:

- ZEN::Mesh3D
- ZEN::Camera3D

@note This document will grow as the entity system gets build.
