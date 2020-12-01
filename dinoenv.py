from __future__ import absolute_import, division, print_function

import base64
import imageio
import IPython
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import PIL.Image
import pyvirtualdisplay

import tensorflow as tf

from tf_agents.agents.dqn import dqn_agent
from tf_agents.drivers import dynamic_step_driver
from tf_agents.environments import suite_gym
from tf_agents.environments import tf_py_environment
from tf_agents.eval import metric_utils
from tf_agents.metrics import tf_metrics
from tf_agents.networks import q_network
from tf_agents.policies import random_tf_policy
from tf_agents.replay_buffers import tf_uniform_replay_buffer
from tf_agents.trajectories import trajectory
from tf_agents.utils import common

from translator import *

class DinoBanditEnv(py_environment.PyEnvironment):

    def __init__(self, cinstance):
        self.cinstance = cinstance
        self._observation_spec = array_spec.BoundedArraySpec(
            shape   = (14,), 
            dtype   = np.int32, 
            minimum = [0,0,0,0,0,0,0,0,0,0,0,0,0,0], 
            maximum = [
                600,150,6,     # Enemy 1
                600,150,6,     # Enemy 2
                600,150,6,     # Enemy 3
                600,150,6,     # Enemy 4
                100,2147483647 # Dino Jump and Score
            ],
            name    = "observation"
        )
        self._action_spec = array_spec.BoundedArraySpec(
            shape   = (), 
            dtype   = np.int32, 
            minimum = 0, # [Jump, None, Duck] 
            maximum = 2, 
            name    = "action"
        )
        super(BanditPyEnvironment, self).__init__()

    # Helper functions.
    def action_spec(self):
        return self._action_spec

    def observation_spec(self):
        return self._observation_spec

    def _empty_observation(self):
        return tf.nest.map_structure(lambda x: np.zeros(x.shape, x.dtype), self.observation_spec())

    # These two functions below should not be overridden by subclasses.
    def _reset(self):
        """Returns a time step containing an observation."""
        return ts.restart(self._observe(), batch_size=self.batch_size)

    def _step(self, action):
        """Returns a time step containing the reward for the action taken."""
        reward = self._apply_action(action)
        return ts.termination(self._observe(), reward)

    # These two functions below are to be implemented in subclasses.
    @abc.abstractmethod
    def _observe(self):
        """Returns an observation."""
        return pyhandlerGetObservation(self.cinstance)

    @abc.abstractmethod
    def _apply_action(self, action):
        """Applies `action` to the Environment and returns the corresponding reward.
        """
        pyhandlerSetAction(self.cinstance, action)

        return pyhandler