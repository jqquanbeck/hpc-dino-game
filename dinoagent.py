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

# === STRAIGHT FROM EXAMPLE ======================
class TwoWayPyEnvironment(BanditPyEnvironment):

  def __init__(self):
    action_spec = array_spec.BoundedArraySpec(
        shape=(), dtype=np.int32, minimum=0, maximum=2, name='action')
    observation_spec = array_spec.BoundedArraySpec(
        shape=(1,), dtype=np.int32, minimum=-2, maximum=2, name='observation')

    # Flipping the sign with probability 1/2.
    self._reward_sign = 2 * np.random.randint(2) - 1
    print("reward sign:")
    print(self._reward_sign)

    super(TwoWayPyEnvironment, self).__init__(observation_spec, action_spec)

  def _observe(self):
    self._observation = np.random.randint(-2, 3, (1,), dtype='int32')
    return self._observation

  def _apply_action(self, action):
    return self._reward_sign * action * self._observation[0]

two_way_tf_environment = tf_py_environment.TFPyEnvironment(TwoWayPyEnvironment())